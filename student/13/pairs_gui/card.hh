/*
 * Class Card
 *
 * Implements a Card, which is inherited from QPushButton
 *
 * Program author
 * Name: Onni Merilä
 * Student number: H299725
 * UserID: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * */
#ifndef CARD_HH
#define CARD_HH

#include <QPushButton>

enum VisibiltyType {OPEN,CLOSE,EMPTY};

class Card : public QPushButton
{
    Q_OBJECT

public:
    Card(const int x, const int y, const char merkki,const QPixmap* image );
    ~Card();

    // Turns the card. If visibilty_ is OPEN, sets the visibilty_ to CLOSE and
    // vice versa
    void turnCard();

    // Sets visibilty_ to EMPTY and sets card disabled so it cannot be clicked
    void eraseCard();

    // Obvious checker methods
    bool isOpen() const;
    bool isEmpty() const;

    // Obvious getter methods
    char getMark() const;

signals:
    // Signal with the cards location info
    void clickSignal(int x,int y);

public slots:
    // Custom slot to emit clickSignal when card is clicked. Connects with
    // QPushButton::clicked signal
    void customClicked();

private:
    // Location of the card
    std::pair<int,int> location_;
    // "Id" of the card
    char mark_;
    // Cards visibilty. Can be "OPEN", "CLOSE" or "EMPTY"
    VisibiltyType visibility_;
    // Used to set different colors for the card
    QPalette* pal_;
    // The image used behind the card
    const QPixmap* backImage;
};

#endif // CARD_HH
