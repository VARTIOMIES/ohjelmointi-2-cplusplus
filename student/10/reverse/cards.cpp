#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int& id)
{
    if (top_!=nullptr)
    {
        id = top_->data;
        top_ = top_->next;
        return true;
    }
   return false;
}

void Cards::reverse()
{
    if (top_ != nullptr)
    {
        std::shared_ptr<Card_data> current = top_;
        std::shared_ptr<Card_data> actual_next = current->next;
        std::shared_ptr<Card_data> next_of_actual_next = actual_next;
        top_->next = nullptr;
        // "Käännetään nuolein suunnat"
        while (next_of_actual_next != nullptr)
        {
            next_of_actual_next = actual_next->next;
            // Kääntö
            actual_next->next = current;

            // Apu osoittimien siirto
            current = actual_next;
            actual_next = next_of_actual_next;
        }
        top_ = current;
    }
}

// Tip for writing code more efficiently:
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
