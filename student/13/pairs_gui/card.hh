#ifndef CARD_HH
#define CARD_HH


enum VisibilityType {OPENED,CLOSED,EMPTY};

class Card
{
public:
    Card(const char& mark);

    VisibilityType getVisibility();

private:
    // Card has different visibilties. If card is turned, it's visibilty_ is
    // "OPENED" etc.
    VisibilityType visbility_;

    // Sort of and "id" of the card
    char mark_;    
};

#endif // CARD_HH
