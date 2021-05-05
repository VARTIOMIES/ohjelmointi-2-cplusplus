#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    int number = 40;

    // Calculate the border lengths of the gameboard
    std::pair<int,int> size = closestFactors(number);

    // Creating gameboard and putting buttons in a grid
    std::vector<Card*> cards = createGameBoard(size.first,size.second);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPressed()
{
    ui->textBrowser->setText("Toimii");
    ui->gridLayout->update();
}

void MainWindow::cardPressed(int x, int y, char merkki)
{
    QString text = "";
    text.push_back(merkki);
    ui->lcdNumber->display(x);
    ui->lcdNumber_2->display(y);
    ui->label->setText(text);
}

std::vector<Card*> MainWindow::createGameBoard(int sizeX, int sizeY)
{
    std::vector<Card*> cards = {};
    ui->gridLayout->setHorizontalSpacing(1);
    ui->gridLayout->setVerticalSpacing(1);
    for(int i=0;i<sizeX;i++)
    {
        for (int j=0;j<sizeY;j++)
        {
            Card* newCard = new Card(i,j,'x');
            cards.push_back(newCard);


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

