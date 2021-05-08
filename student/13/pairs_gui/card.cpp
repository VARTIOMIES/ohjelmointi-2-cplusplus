#include "card.hh"


Card::Card(const int x, const int y, const char merkki):
    location_({x,y}),
    mark_(merkki)
{
    connect(this,&Card::clicked,this,&Card::clickThing);
    setText(QString("HALO"));
    visibility_ = CLOSE;
}

Card::~Card()
{

}

void Card::turnCard()
{
    if (visibility_ == OPEN)
    {
        setText(QString("HALO"));
        visibility_ = CLOSE;
    }
    else if (visibility_ == CLOSE)
    {
        setText((QString(mark_)));
        visibility_ = OPEN;
    }
}

void Card::eraseCard()
{
    visibility_ = EMPTY;
    setText(QString(""));
    setDisabled(true);
}

bool Card::isOpen()
{
    return visibility_ == OPEN;
}

char Card::getMark()
{
    return mark_;
}

void Card::clickThing()
{
    //turnCard();
    emit clickSignal(location_.first,location_.second);
}
