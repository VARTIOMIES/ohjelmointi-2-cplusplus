#include "book.hh"
#include <iostream>
#include "date.hh"

Book::Book(std::string kirjailija,std::string kirjan_nimi):
    kirjailija_(kirjailija),name_(kirjan_nimi)
{
}

void Book::print() const
{
    std::cout << kirjailija_ << " : " << name_ << std::endl;
    if (available_)
    {
        std::cout << "- available" << std::endl;
    }
    else
    {
        std::cout << "- loaned: ";
        loan_day_.print();
        std::cout << "- to be returned: ";
        due_day_.print();
    }
}

void Book::loan(Date date)
{
    if (not available_){
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
    else{
        loan_day_ = date;
        date.advance(28);
        due_day_ = date;
        available_ = false;
    }

}

void Book::renew()
{
    if (available_){
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    } else{
        due_day_.advance(28);
    }
}

void Book::give_back()
{
    available_ = true;
}
