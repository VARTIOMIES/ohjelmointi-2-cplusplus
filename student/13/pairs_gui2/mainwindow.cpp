#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "card.hh"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    int sizeX = 4;
    int sizeY = 4;

    // Peli gridin luonti
    std::vector<Card*> buttons = {};
    std::vector<std::map<Card*,int>> but = {};

    ui->gridLayout->setHorizontalSpacing(1);
    ui->gridLayout->setVerticalSpacing(1);
    for(int i=0;i<sizeX;i++)
    {
        for (int j=0;j<sizeY;j++)
        {
            Card* newCard = new Card(i,j,'x');
            std::map<Card*,int> temp;
            temp.insert({newCard,1});
            but.push_back(temp);

            connect(newCard, &Card::clicked, this, &MainWindow::buttonPressed);
            connect(newCard, &Card::clickSignal, this, &MainWindow::cardPressed);
            newCard->setFixedSize(200,200);
            ui->gridLayout->addWidget(newCard,i,j);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonPressed()
{
    ui->textBrowser->setText("Toimii");
}

void MainWindow::cardPressed(int x, int y, char merkki)
{
    QString text = "";
    text.push_back(merkki);
    ui->lcdNumber->display(x);
    ui->lcdNumber_2->display(y);
    ui->label->setText(text);
}

