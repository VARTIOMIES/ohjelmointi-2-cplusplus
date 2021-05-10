#ifndef SETTINGSWINDOW_HH
#define SETTINGSWINDOW_HH

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>

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
    void settingsDone(int pairAmount, int playerAmount, std::vector<std::string> playerNames);

private slots:
    void settingsButtonPressed();
    void playerAmountValueChanged();
    void pairAmountValueChanged();
    //void()
private:
    Ui::SettingsWindow *ui;
    QGridLayout* wholeLayout;
    QVBoxLayout* settingsLayout;
    QVBoxLayout* playerNameLayout;
    QSlider* pairAmountSlider;
    QSlider* playerAmountSlider;
    QPushButton* settingsReadyButton;
    QLabel* pairAmountLabel;
    QLabel* playerAmountLabel;
    QLabel* pairAmountInfoLabel;
    QLabel* playerAmountInfoLabel;
    std::vector<QLineEdit*> playerNameLineEdits_;

    //std::vector<std::string> playerNames_;

    //int playerAmount;

};

#endif // SETTINGSWINDOW_HH
