#include "card.hh"


Card::Card(const int x, const int y, const char merkki):
    sijainti_({x,y}),
    merkki_(merkki)
{
    connect(this,&Card::clicked,this,&Card::clickThing);

}

Card::~Card()
{

}

void Card::clickThing()
{
    emit clickSignal(sijainti_.first,sijainti_.second,merkki_);
}
