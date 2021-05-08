#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"

#include <QMainWindow>
#include <QTimer>
#include <QLabel>

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
    void buttonPressed();
    void cardPressed(int x, int y);
    void processTwoCards();

private:
    Ui::MainWindow* ui;

    std::vector<Card*> cardsOpened_;

    std::vector<Player*> players_;

    std::vector<Player*>::iterator playerInTurn_;

    void changePlayer();

    GameBoard cards_;

    // Creates a GameBoard filled with cards. Makes a grid size of sizeX * sizeY
    GameBoard createGameBoard(int sizeX, int sizeY);

    // Calculates closest factors of the given number
    std::pair<int,int> closestFactors(int number);

    void askAndCreatePlayersAndLabels(const int playerAmount);

    // Algorithm to randomize the order of cards
    std::vector<std::vector<char>> randomizeMarks(int sizeX,int sizeY);
};
#endif // MAINWINDOW_HH
