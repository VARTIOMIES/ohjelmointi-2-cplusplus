#include "gameboard.hh"


GameBoard::GameBoard(QObject* parent):
    QGraphicsScene(parent)
{
    setSceneRect(0, 0, 100,100);
}

