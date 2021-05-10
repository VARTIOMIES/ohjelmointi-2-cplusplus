/*
 * Class SettingsWindow
 *
 * Implements a Widget used in pairs_gui to edit settings to start a game
 *
 * Program author
 * Name: Onni Merilä
 * Student number: H299725
 * UserID: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * */

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
    // Signal that is emitted when "Start" button is pressed in the program.
    void settingsDone(int pairAmount, int playerAmount,
                      std::vector<std::string> playerNames);

private slots:
    // Slot used to emit a custom signal when "Start" button is pressed
    void settingsButtonPressed();

    // Used to change playerAmountLabel text and add the corresponding amount of
    // lineEdits to change players' names
    void playerAmountValueChanged();

    // Changing pairAmountLabel value to show current value to user
    void pairAmountValueChanged();
private:
    Ui::SettingsWindow *ui;

    // All different ui-elements used in this
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

    // Container storing pointers to all LineEdits to have access to them when
    // emitting settingDone signal
    std::vector<QLineEdit*> playerNameLineEdits_;


};

#endif // SETTINGSWINDOW_HH
