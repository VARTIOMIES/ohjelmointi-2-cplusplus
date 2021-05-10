#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"
#include "settingswindow.hh"

#include <QLayout>
#include <QPushButton>
#include <QGraphicsView>
#include <QSlider>
#include <QLCDNumber>
#include <algorithm>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cardsOpened_(0)
    , playerInTurn_(nullptr)
    , gameBoardWidget(new QWidget(this))
    , playersWidget(new QWidget(this))
    , timeWidget(new QWidget(this))
    , endScreenWidget(new QWidget(this))
    , timer_(new QTimer(this))
    , timerDisplay({nullptr,nullptr})
    , minutes_(0)
    , seconds_(0)
{

    ui->setupUi(this);

    timer_->setInterval(1000);
    connect(timer_,&QTimer::timeout,this,&MainWindow::oneSecondPassed);

    askSettings();
}

MainWindow::~MainWindow()
{

    delete ui;
    delete gameBoardWidget;
    delete playersWidget;
    delete endScreenWidget;
    //delete settingsWidget;
    for (auto player : players_)
    {
        delete player;
    }


}


void MainWindow::startGame(int pairAmount, int playerAmount,
                           std::vector<std::string> names)
{
    int numberOfCards = pairAmount*2;
    // Calculate the border lengths of the gameboard
    std::pair<int,int> size = closestFactors(numberOfCards);
    // Creating gameboard and putting buttons in a grid
    cards_ = createGameBoard(size.first,size.second);

    // Create players and add them to ui
    createPlayersAndLabels(playerAmount, names);

    playerInTurn_ = players_.begin();
    Player* player = *playerInTurn_;
    // Set the first starting player to bolded text
    player->nameLabel->setStyleSheet("font-weight: bold");

    createTimer();
    timer_->start();

}

void MainWindow::cardPressed(int x, int y)
{

    // If cards are spammed, this will stop it
    if (cardsOpened_.size() >= 2)
    {
        return;
    }

    Card* card = cards_.at(x).at(y);
    if (not card->isOpen() and cardsOpened_.size() < 2)
    {
        card->turnCard();
        cardsOpened_.push_back(card);
    }

    if (cardsOpened_.size() >= 2)
    {
        QTimer::singleShot(2000,this,SLOT(processTwoCards()));
    }
}

void MainWindow::processTwoCards()
{
    if (cardsOpened_.at(0)->getMark() == cardsOpened_.at(1)->getMark())
    {
        //Give points to the player in turn
        Player* player = *playerInTurn_;
        player->points++;
        player->pointLabel->setNum(player->points);

        // Erase both cards from the gameboard
        for (auto card : cardsOpened_)
        {
            card->eraseCard();
        }
    }
    else
    {
        for (auto card : cardsOpened_)
        {
            card->turnCard();
        }
        changePlayer();
    }

    cardsOpened_.clear();

    if (isGameBoardEmpty())
    {
        endGame();
    }
}

void MainWindow::oneSecondPassed()
{
    seconds_++;
    if (seconds_ == 60)
    {
        seconds_=0;
        minutes_++;
    }
    timerDisplay.first->display(minutes_);
    timerDisplay.second->display(seconds_);
}

void MainWindow::quitGame()
{
    close();
}

void MainWindow::changePlayer()
{
    Player* player = *playerInTurn_;
    player->nameLabel->setStyleSheet("font-weight: normal");
    playerInTurn_++;
    if (playerInTurn_ == players_.end())
    {
        playerInTurn_ = players_.begin();
    }
    Player* nextPlayer = *playerInTurn_;
    nextPlayer->nameLabel->setStyleSheet("font-weight: bold");
}

void MainWindow::endGame()
{
    timer_->stop();
    gameBoardWidget->setHidden(true);
    playersWidget->setHidden(true);
    timeWidget->setHidden(true);
    setupEndScreen();
    endScreenWidget->setVisible(true);
    ui->verticalLayout->addWidget(endScreenWidget);

}

void MainWindow::askSettings()
{
    SettingsWindow* settingsWindow = new SettingsWindow(this);

    connect(settingsWindow, &SettingsWindow::settingsDone,
            this, &MainWindow::startGame);
    settingsWindow->show();
}

void MainWindow::newGame()
{

    MainWindow* w = new MainWindow();

    w->show();
    close();
}




bool MainWindow::isGameBoardEmpty()
{
    for (auto cardRow : cards_)
    {
        for (auto card : cardRow)
        {
            if (not card->isEmpty())
            {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::createTimer()
{
    QHBoxLayout* timerLayout = new QHBoxLayout(timeWidget);
    QLCDNumber* minuteLCDNumber = new QLCDNumber(timeWidget);
    QLCDNumber* secondLCDNumber = new QLCDNumber(timeWidget);
    minuteLCDNumber->display(minutes_);
    secondLCDNumber->display(seconds_);
    timerLayout->addWidget(minuteLCDNumber);
    timerLayout->addWidget(secondLCDNumber);
    timerDisplay.first = minuteLCDNumber;
    timerDisplay.second = secondLCDNumber;

    ui->verticalLayout->addWidget(timeWidget);
}

GameBoard MainWindow::createGameBoard(int sizeX, int sizeY)
{
    GameBoard cards = {};

    QGridLayout* gameBoardLayout = new QGridLayout(gameBoardWidget);

    gameBoardLayout->setHorizontalSpacing(1);
    gameBoardLayout->setVerticalSpacing(1);

    std::vector<std::vector<char>> marks = randomizeMarks(sizeX,sizeY);
    for(int i=0;i<sizeX;i++)
    {
        cards.push_back({});
        for (int j=0;j<sizeY;j++)
        {
            Card* newCard = new Card(i,j,marks.at(i).at(j));
            cards.at(i).push_back(newCard);


            connect(newCard, &Card::clickSignal, this, &MainWindow::cardPressed);
            newCard->setFixedSize(60,60);

            gameBoardLayout->addWidget(newCard,i,j);
        }
    }
    ui->verticalLayout->addWidget(gameBoardWidget);
    return cards;
}

std::pair<int, int> MainWindow::closestFactors(int number)
{
    int division = 1;
    int factor1 = number;
    int factor2 = 1;
    for (int i = 1; i <= number; ++i){
        // Check if the number is dividable with i
        if (number % i == 0){
           division = number/i;
           if (abs(division-i) < abs(factor1-factor2)){
               factor1 = i;
               factor2 = division;
           }
        }
    }
    // Makes sure that returns smaller factor first in the pair
    if (factor1 > factor2){
        int temp = factor1;
        factor1 = factor2;
        factor2=temp;
    }
    return {factor1,factor2};
}

void MainWindow::createPlayersAndLabels(const int playerAmount,
                                        std::vector<std::string> names)
{
    QHBoxLayout* playerLayout = new QHBoxLayout(playersWidget);
    for (int i = 0;i<playerAmount;i++)
    {
        // Kysy nimeä
        QString name = QString::fromStdString(names.at(i));
        Player* newPlayer = new Player();
        newPlayer->playerName = name.toStdString();
        newPlayer->points = 0;
        players_.push_back(newPlayer);

        // Piirrä pelaajaikkunat
        QLabel* newPlayerNameLabel = new QLabel(playersWidget);
        QLabel* newPlayerPointsLabel = new QLabel(playersWidget);
        newPlayer->pointLabel = newPlayerPointsLabel;
        newPlayer->nameLabel = newPlayerNameLabel;

        QString text = "";
        for (auto character : newPlayer->playerName)
        {
            text.append(character);
        }
        newPlayerNameLabel->setText(text);
        newPlayerPointsLabel->setNum(newPlayer->points);
        playerLayout->addWidget(newPlayerNameLabel);
        playerLayout->addWidget(newPlayerPointsLabel);

    }
    ui->verticalLayout->addWidget(playersWidget);
}


std::vector<std::vector<char> > MainWindow::randomizeMarks(int sizeX, int sizeY)
{
    std::vector<char> allChars = {};
    for(char c = 'a', i = 0; i<sizeX*sizeY/2; ++c, ++i)
    {
        allChars.push_back(c);
        allChars.push_back(c);
    }
    // Randomize the order of the marks
    std::random_device rd;
    auto rng = std::default_random_engine {rd()};
    std::shuffle(std::begin(allChars),std::end(allChars),rng);

    std::vector<char>::const_iterator iterator = allChars.begin();

    std::vector<std::vector<char>>characters = {};
    for(int i=0;i<sizeX;i++)
    {
        characters.push_back({});
        for(int j = 0;j<sizeY;j++)
        {
            characters.at(i).push_back(*iterator);
            iterator++;
        }
    }
    return characters;
}

void MainWindow::setupEndScreen()
{
    QGridLayout* endScreenGrid = new QGridLayout(endScreenWidget);
    QLabel* winTitle = new QLabel(endScreenWidget);
    QLabel* winnertextLabel = new QLabel(endScreenWidget);
    QLabel* winnerNameLabel = new QLabel(endScreenWidget);
    QPushButton* playagainButton = new QPushButton("Play Again",endScreenWidget);
    QPushButton* quitButton = new QPushButton("Quit",endScreenWidget);
    connect(playagainButton,&QPushButton::clicked,this,&MainWindow::newGame);
    connect(quitButton,&QPushButton::clicked,this,&MainWindow::quitGame);


    winTitle->setText("Game ended!");
    winTitle->setStyleSheet("font-size:100px");
    winnertextLabel->setText("Winner:");
    std::string text = findLeader()->playerName;
    QString text1 = QString::fromStdString(text);
    winnerNameLabel->setText(text1);

    QLabel* statsLabel = new QLabel("Stats:",endScreenWidget);
    QLabel* timePassed = new QLabel(endScreenWidget);
    QString temp = "Time passed: ";
    temp+=QString::number(minutes_);
    temp+=" minutes, ";
    temp+=QString::number(seconds_);
    temp+=" seconds.";
    timePassed->setText(temp);

    QVBoxLayout* gameStatsLayout = new QVBoxLayout();
    gameStatsLayout->setAlignment(Qt::AlignLeft);
    gameStatsLayout->setSpacing(0);
    gameStatsLayout->addWidget(statsLabel);
    gameStatsLayout->addWidget(timePassed);

    endScreenGrid->addLayout(gameStatsLayout,3,5,3,3);
    endScreenGrid->addWidget(winTitle,0,1,3,8);
    endScreenGrid->addWidget(winnertextLabel,3,2,2,1);
    endScreenGrid->addWidget(winnerNameLabel,3,3,2,1);
    endScreenGrid->addWidget(quitButton,5,1,1,1);
    endScreenGrid->addWidget(playagainButton,5,2,1,1);

}

Player* MainWindow::findLeader()
{
    Player* leadingPlayer = nullptr;
    int max_points = 0;

    for (auto player : players_)
    {
        if (player->points > max_points)
        {
            leadingPlayer = player;
            max_points = player->points;
        }
    }
    return leadingPlayer;
}
