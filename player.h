#ifndef Player_H
#define Player_H

class Player
{
private:
    char color;

public:
    Player(char color);
    char getColor() const { return color; };
};

#endif // Player_H