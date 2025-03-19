#ifndef Player_H
#define Player_H

#include <vector>
#include <iostream>

class Player
{
private:
    char color;
    int score;
    int possibleMovesCount;

    // clang-format off
    std::vector<std::vector<int> > possibleMoves;
    // clang-format on

public:
    Player(char color);
    char getColor() const { return color; };
    int getScore() const { return score; };
    void incrementScore() { score++; };

    void addPossibleMove(int x, int y);
    void clearPossibleMoves();
    void displayPossibleMoves();
    int getPossibleMovesCount() const { return possibleMovesCount; };
};

#endif // Player_H