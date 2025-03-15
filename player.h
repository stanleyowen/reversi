#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(char color);
    char getColor();
private:
    char color;
};

#endif