#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      cardsOpened_(0)
{

    ui->setupUi(this);

    int number = 40;

    // Calculate the border lengths of the gameboard
    std::pair<int,int> size = closestFactors(number);

    // Creating gameboard and putting buttons in a grid
    cards_ = createGameBoard(size.first,size.second);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPressed()
{
    ui->textBrowser->setText("Toimii");
    //ui->gridLayout->update();
}

void MainWindow::cardPressed(int x, int y, char merkki)
{
    // Bugi jos rämppää ja kaks korttia on jo otettu
    QString text = "";
    text.push_back(merkki);
    ui->lcdNumber->display(x);
    ui->lcdNumber_2->display(y);
    ui->label->setText(text);

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
    if (factor1 > factor2){
        int temp = factor1;
        factor1 = factor2;
        factor2=temp;
    }
    return {factor1,factor2};
}

