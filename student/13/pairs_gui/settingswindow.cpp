#include "settingswindow.hh"
#include "ui_settingswindow.h"



SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
    , settingsLayout(new QVBoxLayout(this))
    , pairAmountSlider(new QSlider(Qt::Horizontal,this))
    , playerAmountSlider(new QSlider(Qt::Horizontal,this))
    , settingsReadyButton(new QPushButton("Start",this))
{
    ui->setupUi(this);

    //QVBoxLayout* settingsLayout = new QVBoxLayout(this);
    //QSlider* pairAmountSlider = new QSlider(this);
    pairAmountSlider->setTickInterval(1);
    pairAmountSlider->setMinimum(2);
    pairAmountSlider->setMaximum(40);


    //QSlider* playerAmountSlider = new QSlider(this);

    playerAmountSlider->setTickInterval(1);
    playerAmountSlider->setMinimum(1);
    playerAmountSlider->setMaximum(10);

    //QPushButton* settingsReadyButton = new QPushButton("Start", this);

    settingsLayout->addWidget(pairAmountSlider);
    settingsLayout->addWidget(playerAmountSlider);
    settingsLayout->addWidget(settingsReadyButton);
    connect(settingsReadyButton,&QPushButton::clicked,
            this,&SettingsWindow::settingsButtonPressed);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::settingsButtonPressed()
{
    int pairAmount = pairAmountSlider->value();
    int playerAmount = playerAmountSlider->value();
    emit(settingsDone(pairAmount,playerAmount));
    close();
}
