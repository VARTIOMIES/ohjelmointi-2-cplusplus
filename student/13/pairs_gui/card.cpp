#include "card.hh"


Card::Card(const int x, const int y, const char merkki):
    sijainti_({x,y}),
    merkki_(merkki)
{
    connect(this,&Card::clicked,this,&Card::clickThing);
    this->setText(QString("HALO"));
    visibility_ = CLOSE;
}

Card::~Card()
{

}

void Card::turnCard()
{
    if (visibility_ == OPEN)
    {
        this->setText(QString("HALO"));
        visibility_ = CLOSE;
    }
    else if (visibility_ == CLOSE)
    {
        this->setText((QString(merkki_)));
        visibility_ = OPEN;
    }
}

void Card::clickThing()
{
    turnCard();
    emit clickSignal(sijainti_.first,sijainti_.second,merkki_);
}
