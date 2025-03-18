#ifndef Player_H
#define Player_H

#include <vector>
#include <iostream>

class Player
{
private:
    char color;
    int score;

    // clang-format off
    std::vector<std::vector<int> > possibleMoves;
    // clang-format on

    int possibleMovesCount;

public:
    Player(char color);
    char getColor() const { return color; };
    int getScore() const { return score; };
    void incrementScore() { score++; };

    void addPossibleMove(int x, int y);
    void clearPossibleMoves();
    void displayPossibleMoves() const
    {
        std::cout << "Possible moves for player " << color << ": ";
        for (int i = 0; i < possibleMovesCount; i++)
        {
            std::cout << "(" << possibleMoves[i][0] << ", " << possibleMoves[i][1] << ") ";
        }
        std::cout << std::endl;
    }
    int getPossibleMovesCount() const { return possibleMovesCount; };
};

#endif // Player_H