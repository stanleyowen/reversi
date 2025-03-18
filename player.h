#ifndef Player_H
#define Player_H

class Player
{
private:
    char color;
    int score;

public:
    Player(char color);
    char getColor() const { return color; };
    int getScore() const { return score; };
    void incrementScore() { score++; };
};

#endif // Player_H