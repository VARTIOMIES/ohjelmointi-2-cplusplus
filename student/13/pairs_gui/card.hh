#ifndef CARD_HH
#define CARD_HH

#include <QPushButton>

enum VisibiltyType {OPEN,CLOSE,EMPTY};
const std::string BACKSIDE_TEXT = "";

class Card : public QPushButton
{
    Q_OBJECT

public:
    Card(const int x, const int y, const char merkki);
    ~Card();
    void turnCard();

signals:
    void clickSignal(int x,int y,char merkki);

public slots:
    void clickThing();

private:

    std::pair<int,int> sijainti_;
    char merkki_;
    VisibiltyType visibility_;
};

#endif // CARD_HH
