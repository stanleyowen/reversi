#include "Player.h"
#include <iostream>

Player::Player(char color) : color(color), score(0)
{
    if (color != 'B' && color != 'W')
    {
        std::cout << "Invalid color. Set to default color 'B'.\n";
        this->color = 'B';
    }
}
