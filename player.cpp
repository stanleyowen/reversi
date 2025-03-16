#include "Player.h"
#include <iostream>

Player::Player(char color) : color(color)
{
    if (color != 'B' && color != 'W')
    {
        std::cout << "Invalid color. Set to default color 'B'.\n";
        this->color = 'B';
    }
}
