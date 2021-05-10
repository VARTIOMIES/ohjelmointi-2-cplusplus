#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QLCDNumber>
#include <QFormLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using GameBoard = std::vector<std::vector<Card*>>;

struct Player {
    std::string playerName;
    int points;
    QLabel* nameLabel;
    QLabel* pointLabel;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startGame(int pairAmount,int playerAmount,std::vector<std::string> names);
    void cardPressed(int x, int y);
    void quitGame();

private slots:
    void processTwoCards();
    void oneSecondPassed();

private:
    Ui::MainWindow* ui;

    std::vector<Card*> cardsOpened_;

    std::vector<Player*> players_;

    std::vector<Player*>::iterator playerInTurn_;

    void changePlayer();

    void endGame();

    void askSettings();

    void newGame();

    // Checks if the GameBoard is empty. Returns true if every cardslot is empty
    bool isGameBoardEmpty();

    void createTimer();

    GameBoard cards_;

    // Creates a GameBoard filled with cards. Makes a grid size of sizeX * sizeY
    GameBoard createGameBoard(int sizeX, int sizeY);

    // Calculates closest factors of the given number
    std::pair<int,int> closestFactors(int number);

    void createPlayersAndLabels(const int playerAmount,
                                std::vector<std::string> names);

    // Algorithm to randomize the order of cards
    std::vector<std::vector<char>> randomizeMarks(int sizeX,int sizeY);

    QWidget* gameBoardWidget;
    
    QWidget* playersWidget;

    QWidget* timeWidget;

    QWidget* endScreenWidget;

    void setupEndScreen();

    Player* findLeader();

    QTimer* timer_;

    std::pair<QLCDNumber*,QLCDNumber*> timerDisplay;

    // Jos tarvii
    int minutes_;
    int seconds_;
};
#endif // MAINWINDOW_HH
