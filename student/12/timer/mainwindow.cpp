#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),
    ui(new Ui::MainWindow),
    seconds(0),
    minutes(0)
{
    ui->setupUi(this);
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout , this, &MainWindow::one_second_passed);

    ui->lcdNumberMin->setStyleSheet("background:#000123;");
    ui->lcdNumberSec->setStyleSheet("background:#000123;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stopButton_clicked()
{
    if (timer->isActive())
    {
        timer->stop();
    }
}

void MainWindow::on_startButton_clicked()
{
    if (!timer->isActive())
    {
        timer->start();
    }

}

void MainWindow::on_resetButton_clicked()
{
    if (!timer->isActive())
    {
        seconds = 0;
        minutes = 0;
        //update_displays();
    }
    ui->lcdNumberSec->display(0);
    ui->lcdNumberMin->display(0);
}

void MainWindow::one_second_passed()
{
    seconds += 1;
    if (seconds >= 60)
    {
        minutes += 1;
        seconds = 0;
    }
    update_displays();
}

void MainWindow::update_displays()
{
    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);
}
