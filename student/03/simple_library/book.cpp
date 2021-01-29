#include "book.hh"
#include <iostream>
#include "date.hh"

Book::Book()
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

}

void Book::renew()
{

}

void Book::give_back()
{

}
