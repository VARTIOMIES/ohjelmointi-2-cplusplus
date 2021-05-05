#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void buttonPressed();
    void cardPressed(int x, int y, char merkki);

private:
    Ui::MainWindow* ui;

    std::vector<Card*> createGameBoard(int sizeX, int sizeY);

    // Calculates closest factors of the given number
    std::pair<int,int> closestFactors(int number);
};
#endif // MAINWINDOW_HH
