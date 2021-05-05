#ifndef CARD_HH
#define CARD_HH

#include <QPushButton>

class Card : public QPushButton
{
    Q_OBJECT

public:
    Card(const int x, const int y, const char merkki);
    ~Card();

signals:
    void clickSignal(int x,int y,char merkki);

public slots:
    void clickThing();

private:
    std::pair<int,int> sijainti_;
    char merkki_;
};

#endif // CARD_HH
