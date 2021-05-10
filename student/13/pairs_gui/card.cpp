#include "card.hh"


Card::Card(const int x, const int y, const char merkki):
    location_({x,y}),
    mark_(merkki),
    pal_(new QPalette())
{
    connect(this,&Card::clicked,this,&Card::clickThing);
    setText(QString("Onnin \n MUISTI- \n PELI"));
    visibility_ = CLOSE;
    setAutoFillBackground(true);
    //QPalette pal = palette();
    pal_->setColor(QPalette::Button,QColor(Qt::red));

    setPalette(*pal_);

}

Card::~Card()
{

}

void Card::turnCard()
{
    if (visibility_ == OPEN)
    {
        setText(QString("Onnin \n MUISTI- \n PELI"));
        visibility_ = CLOSE;
        pal_->setColor(QPalette::Button,QColor(Qt::red));
    }
    else if (visibility_ == CLOSE)
    {
        setText((QString(mark_)));
        visibility_ = OPEN;
        pal_->setColor(QPalette::Button,QColor(Qt::white));
    }
    setPalette(*pal_);
}

void Card::eraseCard()
{
    visibility_ = EMPTY;
    setText(QString(""));
    setDisabled(true);
    pal_->setColor(QPalette::Button,QColor(Qt::gray));
    setPalette(*pal_);
}

bool Card::isOpen()
{
    return visibility_ == OPEN;
}

bool Card::isEmpty()
{
    return visibility_ == EMPTY;
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
