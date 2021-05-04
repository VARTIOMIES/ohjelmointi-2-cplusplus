#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH
/*
 *
 * */

#include "card.hh"

#include <QGraphicsScene>


class GameBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    GameBoard(QObject* parent = nullptr);

    // Flips the card graphics
    void flipCard(int x,int y);

    // Makes card removed graphics
    void removeCard(int x,int y);

    // Adds the card to the given player
    void addCardToPlayer(int x,int y,std::string player);



};

#endif // GAMEBOARD_HH
