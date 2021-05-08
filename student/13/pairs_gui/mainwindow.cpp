#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"

#include <QPushButton>
#include <QGraphicsView>
#include <algorithm>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      cardsOpened_(0),
      playerInTurn_(nullptr)
{

    ui->setupUi(this);

    int number = 24;

    // Calculate the border lengths of the gameboard
    std::pair<int,int> size = closestFactors(number);

    // Creating gameboard and putting buttons in a grid
    cards_ = createGameBoard(size.first,size.second);

    int playerAmount = 4;
    // Create players and add them to ui
    askAndCreatePlayersAndLabels(playerAmount);


    playerInTurn_ = players_.begin();
    Player* player = *playerInTurn_;
    player->nameLabel->setStyleSheet("font-weight: bold");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPressed()
{

    //ui->gridLayout->update();
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

GameBoard MainWindow::createGameBoard(int sizeX, int sizeY)
{
    GameBoard cards = {};
    ui->gridLayout->setHorizontalSpacing(1);
    ui->gridLayout->setVerticalSpacing(1);

    std::vector<std::vector<char>> marks = randomizeMarks(sizeX,sizeY);
    for(int i=0;i<sizeX;i++)
    {
        cards.push_back({});
        for (int j=0;j<sizeY;j++)
        {
            Card* newCard = new Card(i,j,marks.at(i).at(j));
            cards.at(i).push_back(newCard);


            connect(newCard, &Card::clicked, this, &MainWindow::buttonPressed);
            connect(newCard, &Card::clickSignal, this, &MainWindow::cardPressed);
            newCard->setFixedSize(60,60);

            ui->gridLayout->addWidget(newCard,i,j);
        }
    }
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

void MainWindow::askAndCreatePlayersAndLabels(const int playerAmount)
{
    for (int i = 0;i<playerAmount;i++)
    {
        // Kysy nimeä
        QString name = "Pelaajax";
        Player* newPlayer = new Player();
        newPlayer->playerName = name.toStdString();
        newPlayer->points = 0;
        players_.push_back(newPlayer);

        // Piirrä pelaajaikkunat
        QLabel* newPlayerNameLabel = new QLabel(this);
        QLabel* newPlayerPointsLabel = new QLabel(this);
        newPlayer->pointLabel = newPlayerPointsLabel;
        newPlayer->nameLabel = newPlayerNameLabel;

        QString text = "";
        for (auto character : newPlayer->playerName)
        {
            text.append(character);
        }
        newPlayerNameLabel->setText(text);
        newPlayerPointsLabel->setNum(newPlayer->points);

        ui->horizontalLayout->addWidget(newPlayerNameLabel);
        ui->horizontalLayout->addWidget(newPlayerPointsLabel);
    }
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

