#include "settingswindow.hh"
#include "ui_settingswindow.h"



SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
    , settingsLayout(new QVBoxLayout(this))
    , pairAmountSlider(new QSlider(Qt::Horizontal,this))
    , playerAmountSlider(new QSlider(Qt::Horizontal,this))
    , settingsReadyButton(new QPushButton("Start",this))
    , pairAmountLabel(new QLabel(this))
    , playerAmountLabel(new QLabel(this))
    , pairAmountInfoLabel(new QLabel("Number of pairs:",this))
    , playerAmountInfoLabel(new QLabel("Number of players",this))

{
    ui->setupUi(this);

    // Fixing settings of all the widgets
    pairAmountSlider->setTickInterval(1);
    pairAmountSlider->setMinimum(2);
    pairAmountSlider->setMaximum(40);

    pairAmountLabel->setNum(pairAmountSlider->value());
    //
    playerAmountSlider->setTickInterval(1);
    playerAmountSlider->setMinimum(1);
    playerAmountSlider->setMaximum(10);

    playerAmountLabel->setNum(playerAmountSlider->value());

    // Adding the subwidgets to the main widgets layout
    settingsLayout->addWidget(pairAmountInfoLabel);
    settingsLayout->addWidget(pairAmountLabel);
    settingsLayout->addWidget(pairAmountSlider);
    settingsLayout->addWidget(playerAmountInfoLabel);
    settingsLayout->addWidget(playerAmountLabel);
    settingsLayout->addWidget(playerAmountSlider);
    settingsLayout->addWidget(settingsReadyButton);

    // Connection from the pushbutton to slot
    connect(settingsReadyButton,&QPushButton::clicked,
            this,&SettingsWindow::settingsButtonPressed);
    // Connection from sliders to labels
    connect(pairAmountSlider,&QSlider::valueChanged,
            this,&SettingsWindow::pairAmountValueChanged);
    connect(playerAmountSlider,&QSlider::valueChanged,
            this,&SettingsWindow::playerAmountValueChanged);
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

void SettingsWindow::playerAmountValueChanged()
{
    playerAmountLabel->setNum(playerAmountSlider->value());
}

void SettingsWindow::pairAmountValueChanged()
{
    pairAmountLabel->setNum(pairAmountSlider->value());
}
