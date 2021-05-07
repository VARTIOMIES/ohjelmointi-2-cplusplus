#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "card.hh"

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using GameBoard = std::vector<std::vector<Card*>>;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void buttonPressed();
    void cardPressed(int x, int y, char merkki);
    void processTwoCards();

private:
    Ui::MainWindow* ui;

    std::vector<Card*> cardsOpened_;

    GameBoard cards_;

    // Creates a GameBoard filled with cards. Makes a grid size of sizeX * sizeY
    GameBoard createGameBoard(int sizeX, int sizeY);

    // Calculates closest factors of the given number
    std::pair<int,int> closestFactors(int number);
};
#endif // MAINWINDOW_HH
