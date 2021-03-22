#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards():top_(nullptr), bottom_(nullptr)
{

}

Cards::~Cards()
{
    while(top_ != nullptr)
    {
        Card_data* card_to_release = top_;
        top_ = top_->next;

        delete card_to_release;
    }
}



void Cards::add(int id)
{
    Card_data* new_card = new Card_data{id,nullptr};
    if (top_ == nullptr)
    {
        top_ = new_card;
        bottom_ = new_card;
    }
    else
    {
        new_card->next = top_;
        top_ = new_card;
    }

}

void Cards::print_from_top_to_bottom(std::ostream& s)
{
    Card_data* card_to_print = top_;

    int running_number = 1;
    while (card_to_print != nullptr)
    {
        s << running_number << ": " <<card_to_print->data<< std::endl;
        card_to_print = card_to_print->next;
        running_number++;
    }
}

bool Cards::remove(int& id)
{
    if (isEmpty())
    {
        return false;
    }
    Card_data* card_to_remove = top_;

    id = card_to_remove->data;

    if (top_ == bottom_)
    {
        top_ = nullptr;
        bottom_ = nullptr;
    }
    else
    {
        top_ = top_->next;
    }
    delete card_to_remove;

    return true;
}

bool Cards::bottom_to_top()
{
    if (isEmpty())
    {
        return false;
    }
    bottom_->next = top_;
    top_ = bottom_;
    Card_data* kortti = top_;
    // Poistetaan uuden pohjimmaisen kortin next
    while (true)
    {
        if (kortti->next == bottom_)
        {
            bottom_ = kortti;
            kortti->next =nullptr;
            break;
        }
        kortti = kortti->next;
    }

    return true;
}

bool Cards::top_to_bottom()
{
    if (isEmpty())
    {
        return false;
    }
    bottom_->next = top_;
    Card_data* old_top = top_;
    top_ = top_->next;
    bottom_ = old_top;
    bottom_->next=nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_,s);

}

bool Cards::isEmpty()
{
    return top_ == nullptr;
}

int Cards::recursive_print(Cards::Card_data* top, std::ostream &s)
{
    // Alustetaan ensimmäiseksi järjestysnumeroksi 1
    int order = 1;

    // Jos ei olla viimeisessä kortissa, mennään syvemmälle
    if (top != bottom_)
    {
        // Rekursiivisesti mennään seuraavaan korttiin. Viimeinen rekursion
        // osa palauttaa 2, sitä seuraava 3 jne...
        order = recursive_print(top->next,s);
    }
    // Tulostetaan. Ensimmäisellä kerralla kun ollaan täällä, ollaan viimeisessä
    // kortissa. Tulostetaan, ja palautetaan yhtä suurempi järjestysnumero, joka
    // on seuraavan kortin tulostuksen järjestysnumero, eli 1,2,3.....
    s <<order<<": "<< top->data<<std::endl;
   return order+1;
}
