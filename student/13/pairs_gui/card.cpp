/*
 * Program author
 * Name: Onni Merilä
 * Student number: H299725
 * UserID: bvonme
 * E-Mail: onni.merila@tuni.fi
 *
 * */
#include "card.hh"


Card::Card(const int x, const int y, const char merkki,const QPixmap* image):
    location_({x,y}),
    mark_(merkki),
    pal_(new QPalette()),
    backImage(image)
{
    backImage->scaled(this->size());
    setIcon(*backImage);
    visibility_ = CLOSE;

    connect(this,&Card::clicked,this,&Card::customClicked);

    setAutoFillBackground(true);
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
        setText(QString(""));
        visibility_ = CLOSE;
        pal_->setColor(QPalette::Button,QColor(Qt::red));
        setIcon(*backImage);

    }
    else if (visibility_ == CLOSE)
    {
        setText((QString(mark_)));
        visibility_ = OPEN;
        pal_->setColor(QPalette::Button,QColor(Qt::white));
        setIcon(QIcon());
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
    setIcon(QIcon());
}

bool Card::isOpen() const
{
    return visibility_ == OPEN;
}

bool Card::isEmpty() const
{
    return visibility_ == EMPTY;
}

char Card::getMark() const
{
    return mark_;
}

void Card::customClicked()
{
    emit clickSignal(location_.first,location_.second);
}
