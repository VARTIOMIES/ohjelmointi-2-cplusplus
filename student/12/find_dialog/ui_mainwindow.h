/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_file;
    QCheckBox *matchCheckBox;
    QPushButton *closePushButton;
    QLineEdit *keyLineEdit;
    QLineEdit *fileLineEdit;
    QPushButton *findPushButton;
    QLabel *label_what_to_find;
    QFrame *line;
    QLabel *label_3;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(150, 20, 361, 209));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_file = new QLabel(verticalLayoutWidget);
        label_file->setObjectName(QString::fromUtf8("label_file"));

        gridLayout->addWidget(label_file, 0, 0, 1, 1);

        matchCheckBox = new QCheckBox(verticalLayoutWidget);
        matchCheckBox->setObjectName(QString::fromUtf8("matchCheckBox"));

        gridLayout->addWidget(matchCheckBox, 2, 0, 1, 1);

        closePushButton = new QPushButton(verticalLayoutWidget);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));

        gridLayout->addWidget(closePushButton, 1, 2, 1, 1);

        keyLineEdit = new QLineEdit(verticalLayoutWidget);
        keyLineEdit->setObjectName(QString::fromUtf8("keyLineEdit"));

        gridLayout->addWidget(keyLineEdit, 1, 1, 1, 1);

        fileLineEdit = new QLineEdit(verticalLayoutWidget);
        fileLineEdit->setObjectName(QString::fromUtf8("fileLineEdit"));

        gridLayout->addWidget(fileLineEdit, 0, 1, 1, 1);

        findPushButton = new QPushButton(verticalLayoutWidget);
        findPushButton->setObjectName(QString::fromUtf8("findPushButton"));

        gridLayout->addWidget(findPushButton, 0, 2, 1, 1);

        label_what_to_find = new QLabel(verticalLayoutWidget);
        label_what_to_find->setObjectName(QString::fromUtf8("label_what_to_find"));

        gridLayout->addWidget(label_what_to_find, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(closePushButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_file->setText(QCoreApplication::translate("MainWindow", "Find from file:", nullptr));
        matchCheckBox->setText(QCoreApplication::translate("MainWindow", "Match case", nullptr));
        closePushButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        findPushButton->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        label_what_to_find->setText(QCoreApplication::translate("MainWindow", "Find what:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Search status:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
