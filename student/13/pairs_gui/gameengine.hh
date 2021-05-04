#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include "gameboard.hh"
#include "card.hh"

#include <random>

struct Player {
    std::string name;
    int amountOfCards;
};

class GameEngine
{
public:
    GameEngine(GameBoard& gameBoard);

signals:
    void quitGame();

public slots:

    void flipCard(int x,int y);


private:
    // Method to fill the gameboard with cards in the beginning
    void fillGameBoardWithCards(GameBoard* gameBoard);

    // Game board used in the game
    std::vector< std::vector< std::shared_ptr<Card*> > > board_;

    // Drawing area to show the game status
    GameBoard& graphicalGameBoard_;

    // Random number generator
    std::default_random_engine generator;
};

#endif // GAMEENGINE_HH
