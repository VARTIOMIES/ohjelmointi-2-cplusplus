#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "gameengine.hh"
#include <QGraphicsView>

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameBoard &scene,QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsView view_;
};
#endif // MAINWINDOW_HH
