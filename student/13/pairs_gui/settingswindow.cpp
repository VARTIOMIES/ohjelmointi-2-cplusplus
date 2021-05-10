#include "settingswindow.hh"
#include "ui_settingswindow.h"



SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWindow)
    , wholeLayout(new QGridLayout(this))
    , settingsLayout(new QVBoxLayout())
    , playerNameLayout(new QVBoxLayout())
    , pairAmountSlider(new QSlider(Qt::Horizontal))
    , playerAmountSlider(new QSlider(Qt::Horizontal))
    , settingsReadyButton(new QPushButton("Start"))
    , pairAmountLabel(new QLabel())
    , playerAmountLabel(new QLabel())
    , pairAmountInfoLabel(new QLabel("Number of pairs:"))
    , playerAmountInfoLabel(new QLabel("Number of players"))
    , playerNameLineEdits_({})
    //, playerNames_({})
    //, playerAmount(0)

{
    ui->setupUi(this);

    wholeLayout->addLayout(settingsLayout,0,0,15,5);
    wholeLayout->addLayout(playerNameLayout,2,5,13,3);

    // Fixing settings of all the widgets
    pairAmountSlider->setTickInterval(1);
    pairAmountSlider->setMinimum(2);
    pairAmountSlider->setMaximum(40);

    pairAmountLabel->setNum(pairAmountSlider->value());
    //
    playerAmountSlider->setTickInterval(1);
    playerAmountSlider->setMinimum(1);
    playerAmountSlider->setMaximum(8);

    playerAmountLabel->setNum(playerAmountSlider->value());

    // Adding the subwidgets to the main widgets layout
    settingsLayout->addWidget(pairAmountInfoLabel);
    settingsLayout->addWidget(pairAmountLabel);
    settingsLayout->addWidget(pairAmountSlider);
    settingsLayout->addWidget(playerAmountInfoLabel);
    settingsLayout->addWidget(playerAmountLabel);
    settingsLayout->addWidget(playerAmountSlider);
    settingsLayout->addWidget(settingsReadyButton);

    QLabel* playerNameInfoLabel = new QLabel("Players:",this);
    wholeLayout->addWidget(playerNameInfoLabel,1,5,1,1);

    QLineEdit* newLineEdit = new QLineEdit(this);

    QString preGeneratedName = "Player ";
    preGeneratedName.append(QString::number(1));

    newLineEdit->setText(preGeneratedName);
    playerNameLayout->addWidget(newLineEdit);
    playerNameLineEdits_.push_back(newLineEdit);



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
    pairAmountSlider->setDisabled(true);
    playerAmountSlider->setDisabled(true);

    int pairAmount = pairAmountSlider->value();
    int playerAmount = playerAmountSlider->value();
    std::vector<std::string> playerNames = {};

    for (auto nameLineEdit : playerNameLineEdits_)
    {
        playerNames.push_back(nameLineEdit->text().toStdString());
    }

    emit(settingsDone(pairAmount,playerAmount,playerNames));
    close();
}

void SettingsWindow::playerAmountValueChanged()
{
    int playerAmount = playerAmountSlider->value();
    playerAmountLabel->setNum(playerAmount);
    QLayoutItem* child;
    while ((child = playerNameLayout->takeAt(0)) != nullptr)
    {

        delete child->widget();
    }
    playerNameLineEdits_.clear();

    for (int i = 1;i<=playerAmount;i++)
    {
        QLineEdit* newLineEdit = new QLineEdit(this);

        QString preGeneratedName = "Player ";
        preGeneratedName.append(QString::number(i));

        newLineEdit->setText(preGeneratedName);
        playerNameLayout->addWidget(newLineEdit);
        playerNameLineEdits_.push_back(newLineEdit);
    }

}

void SettingsWindow::pairAmountValueChanged()
{
    pairAmountLabel->setNum(pairAmountSlider->value());
}
