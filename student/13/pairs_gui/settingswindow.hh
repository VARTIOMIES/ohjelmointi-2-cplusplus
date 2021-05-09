#ifndef SETTINGSWINDOW_HH
#define SETTINGSWINDOW_HH

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
signals:
    void settingsDone(int pairAmount, int playerAmount);

private slots:
    void settingsButtonPressed();
    void playerAmountValueChanged();
    void pairAmountValueChanged();
private:
    Ui::SettingsWindow *ui;
    QVBoxLayout* settingsLayout;
    QSlider* pairAmountSlider;
    QSlider* playerAmountSlider;
    QPushButton* settingsReadyButton;
    QLabel* pairAmountLabel;
    QLabel* playerAmountLabel;
    QLabel* pairAmountInfoLabel;
    QLabel* playerAmountInfoLabel;

};

#endif // SETTINGSWINDOW_HH
