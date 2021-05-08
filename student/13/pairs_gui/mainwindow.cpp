#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"

#include <QPushButton>
#include <QGraphicsView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      cardsOpened_(0),
      playerInTurn_(nullptr)
{

    ui->setupUi(this);

    int number = 20;

    // Calculate the border lengths of the gameboard
    std::pair<int,int> size = closestFactors(number);

    // Creating gameboard and putting buttons in a grid
    cards_ = createGameBoard(size.first,size.second);

    int playerAmount = 2;



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

        QString text = "";
        for (auto character : newPlayer->playerName)
        {
            text.append(character);
        }
        newPlayerNameLabel->setText(text);
        newPlayerPointsLabel->setNum(newPlayer->points);

        ui->horizontalLayout->addWidget(newPlayerNameLabel);
        ui->horizontalLayout->addWidget(newPlayerPointsLabel);

        /*
        QGraphicsView* view_ = new QGraphicsView(this);

        view_->setGeometry(20,
                           350,
                           20 + 10 * (20 + 20),
                           20 + 30 + 20);

        QGraphicsScene* scene = new QGraphicsScene(this);


        // TODO
        QVerticalLayout* newPlayerFrame = new QFrame();
        newPlayerFrame->add

        QGraphicsView* newPlayerWindow = new QGraphicsView();

        scene->addText(name);
        QGraphicsView view(scene);
        view.show();
        ui->horizontalLayout->addWidget(newPlayerWindow);
        */
    }
    playerInTurn_ = players_.begin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPressed()
{

    //ui->gridLayout->update();
}

void MainWindow::cardPressed(int x, int y, char merkki)
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
    }
    playerInTurn_++;
    if (playerInTurn_ == players_.end())
    {
        playerInTurn_ = players_.begin();
    }

    cardsOpened_.clear();


}

GameBoard MainWindow::createGameBoard(int sizeX, int sizeY)
{
    GameBoard cards = {};
    ui->gridLayout->setHorizontalSpacing(1);
    ui->gridLayout->setVerticalSpacing(1);
    for(int i=0;i<sizeX;i++)
    {
        cards.push_back({});
        for (int j=0;j<sizeY;j++)
        {
            Card* newCard = new Card(i,j,'x');
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

