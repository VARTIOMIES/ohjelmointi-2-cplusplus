#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->findPushButton, &QPushButton::clicked , this , &MainWindow::on_findPushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findPushButton_clicked()
{
    std::string filename = filename_;
    std::ifstream file(filename);
    if (!file)
    {
        ui->textBrowser->setText("File not found");
        return;
    }
    else if (what_to_find_.size()==0)
    {
        ui->textBrowser->setText("File found");
        return;
    }

    std::string rivi = "";
    bool found = false;
    std::string sub_str = what_to_find_;
    while(std::getline(file,rivi))
    {
        if (!ui->matchCheckBox->isChecked())
        {
            for(char& chara : sub_str)
            {
                chara = tolower(chara);
            }
        }
        if (rivi.find(sub_str) != std::string::npos)
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        ui->textBrowser->setText("Word found");
        return;
    }
    else
    {
        ui->textBrowser->setText("Word not found");
        return;
    }
}

void MainWindow::on_keyLineEdit_editingFinished()
{
    what_to_find_ = ui->keyLineEdit->text().toStdString();
}

void MainWindow::on_fileLineEdit_editingFinished()
{

    filename_ = ui->fileLineEdit->text().toStdString();
}
