/*
 * Class MainWindow
 *
 * Implements a Pairs game and user interface
 *
 * Program author
 * Name: Onni Merilä
 * Student number: H299725
 * UserID: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QLCDNumber>
#include <QFormLayout>
#include <QLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <algorithm>
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using GameBoard = std::vector<std::vector<Card*>>;

// Implements a player object used in the game. Stores labels that store some
// information about the player, and need to be accessed during the game
struct Player {
    std::string playerName;
    int points;
    std::vector<char> cardStack;
    QLabel* nameLabel;
    QLabel* pointLabel;
    QLabel* cardsLabel;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // Starts the game. Needs parameters to create a gameboard containing
    // a wanted amount of cards and wanted amunt of players with wanted names
    void startGame(int pairAmount,int playerAmount,
                   std::vector<std::string> names);
    // Turns the card that is clicked. Checks, if two cards are opened and
    // after a delay, calls for processTwoCards(). Has an antispam mechanism
    void cardPressed(int x, int y);
    // Closes the game with close() command
    void quitGame();

private slots:
    // Checks if the two cards opened are pairs or not. If the cards are a pair
    // (both cards have the same letter/id) adds pair to the player who opened
    // the cards, updates labels and erases cards from the gameboard. If the
    // cards opened are not a pair, turns the cards upsidedown and moves turn
    // to the next player.
    void processTwoCards();

    // Adds one second to the timer. Checks if 1 minute (60 seconds) has passed
    // and changes second passed to minutes passed.
    void oneSecondPassed();

private:


    Ui::MainWindow* ui;

    // Stores pointers to cards that are opened. Used to only let 2 cards be
    // open at the same time.
    std::vector<Card*> cardsOpened_;

    // Stores pointers to all players
    std::vector<Player*> players_;

    // Iterator of players_ vector. Points to playerpointer whose turn it is
    std::vector<Player*>::iterator playerInTurn_;

    // Changes the playerInTurn_ iterator to point to the next player in turn.
    void changePlayer();

    // Ends the game and sets up the endscreen
    void endGame();

    // Opens the settings widget which will start the game later
    void askSettings();

    // Closes current game and starts a new one.
    void newGame();

    // Checks if the GameBoard is empty. Returns true if every cardslot is empty
    bool isGameBoardEmpty();

    // Creates the timer widget that is visible during the game
    void createTimer();

    // Contains all Cardpointers in the game
    GameBoard cards_;

    // Creates a GameBoard filled with cards. Makes a grid size of sizeX * sizeY
    GameBoard createGameBoard(int sizeX, int sizeY);

    // Calculates closest factors of the given number
    std::pair<int,int> closestFactors(int number);

    // Creates players and adds needed labels to ui
    void createPlayersAndLabels(const int playerAmount,
                                std::vector<std::string> names);

    // Algorithm to randomize the order of cards
    std::vector<std::vector<char>> randomizeMarks(int sizeX,int sizeY);

    // Widget that has all the card pushbuttons in it.
    QWidget* gameBoardWidget;
    
    // Widget that has all the labels relating to players
    QWidget* playersWidget;

    // Widget that has the timer visible during the game
    QWidget* timeWidget;

    // Widget that has every sub-widget visible after the game has ended.
    QWidget* endScreenWidget;

    // Creates the endscreen by adding all ui-elements into endScreenWidget
    void setupEndScreen();

    // Helpermethod to find the player that has the most points
    Player* findLeader();

    // Checks if there are players with the same points
    bool isTie();

    // Timer used in timeWidget
    QTimer* timer_;

    // Contains the displays for the timeWidget
    std::pair<QLCDNumber*,QLCDNumber*> timerDisplay;

    // Time passed during the game as integer values
    int minutes_;
    int seconds_;
};
#endif // MAINWINDOW_HH
