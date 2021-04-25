#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countButton_clicked()
{
    int weight = std::stoi(ui->weightLineEdit->text().toStdString());
    int height = std::stoi(ui->heightLineEdit->text().toStdString());

    double result = weight/((height/100.0)*(height/100.0));

    ui->resultLabel->setNum(result);
    if (result < 18.5)
    {
        ui->infoTextBrowser->setText(QString("You are underweight."));
    }
    else if (result > 25.0)
    {
        ui->infoTextBrowser->setText(QString("You are overweight."));
    }
    else
    {
        ui->infoTextBrowser->setText(QString("Your weight is normal."));
    }
}
