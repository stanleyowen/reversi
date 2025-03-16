#ifndef Game_H
#define Game_H

#include "Board.h"
#include "Player.h"

class Game
{
public:
    Game();
    void start();

private:
    Board board;
    Player playerA;
    Player playerB;
    Player *currentPlayer;

    bool isGameOver();
    void switchTurn();
};

#endif // Game_H