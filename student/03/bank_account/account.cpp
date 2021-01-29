#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner),credit_card_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
void Account::print() const
{
    std::cout << owner_<< " : " << iban_ << " : " << balance_ << " euros" << std::endl;

}
bool Account::set_credit_limit(int limit)
{
    if (credit_card_)
    {
        credit_limit_ = limit;
        return true;
    }
    else
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
        return false;
    }
}
void Account::save_money(int amount)
{
    Account::balance_ += amount;
}
bool Account::take_money(int amount)
{
    if (balance_ >= amount)
    {
        balance_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
        return true;
    }
    else if (credit_card_){
        if (balance_ >= 0 and balance_+credit_limit_ >= amount){
            balance_ -=amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
            return true;
        }
        else if (abs(balance_ - amount) <= credit_limit_){
            balance_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
            return true;
        }
        else {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Cannot take money: balance underflow" << std::endl;
        return false;
    }

}
void Account::transfer_to(Account& x, int amount)
{
    if (take_money(amount))
    {
        x.save_money(amount);
    }
    else
    {
        std::cout << "Transfer from " << iban_ << " failed"<< std::endl;

    }

}

