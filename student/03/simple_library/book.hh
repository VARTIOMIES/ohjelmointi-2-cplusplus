#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include "date.hh"


class Book
{
public:
    // Constructor
    Book(std::string kirjailija,std::string kirjan_nimi);
    // Methods
    void print() const;
    void loan(Date date);
    void renew();
    void give_back();

private:
    std::string kirjailija_;
    std::string name_;
    bool available_ = true;
    Date loan_day_;
    Date due_day_;


};

#endif // BOOK_HH
