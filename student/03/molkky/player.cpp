#include "player.hh"

Player::Player(std::string player):
    name_(player),points_(0)
{
}

std::string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}

void Player::add_points(int points)
{
    points_ += points;
    if (points_ > 50){
        points_ = 25;
        std::cout << get_name() << " gets penalty points!" << std::endl;
    }
}

bool Player::has_won()
{
    if (points_ == 50){
        return true;
    }else {
        return false;
    }
}
