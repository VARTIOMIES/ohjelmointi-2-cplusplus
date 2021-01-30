#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>
#include <string>


class Player
{
public:
    Player(std::string player);
    std::string get_name();
    int get_points();
    void add_points(int points);
    bool has_won();
private:
    std::string name_;
    int points_;

};

#endif // PLAYER_HH
