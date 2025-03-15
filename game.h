#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

class Game {
public:
    Game();
    void start();
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;
    bool isGameOver();
    void switchTurn();
};

#endif