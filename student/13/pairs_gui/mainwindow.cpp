#include "mainwindow.hh"
#include "gameengine.hh"

#include "ui_mainwindow.h"

MainWindow::MainWindow(GameBoard& scene, QWidget* parent) :
    QMainWindow(parent),
    view_(this)

{
   view_.setScene(&scene);
   setCentralWidget(&view_)

}

