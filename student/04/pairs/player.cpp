#include "player.hh"
#include <iostream>

// Lisää luokan toteutus tähän.
// Kuhunkin julkiseen metodiin pitäisi riittää 1-2 koodiriviä.

// Add class implementation here.
// It should be enough to write only 1-2 code lines in each public method.

Player::Player(const std::string& name): name_(name), pairs_(0)
{

}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return pairs_;
}

void Player::add_card(Card& card)
{
    card.remove_from_game_board();
    pairs_++;
}

void Player::print() const
{
    std::cout << "*** " << name_ << " has " << pairs_ << " pair(s)." << std::endl;
}
