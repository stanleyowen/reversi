#ifndef Game_H
#define Game_H

// Include necessary headers
#include "Board.h"
#include "Player.h"

class Game
{
public:
    Game();       // Default constructor to initialize the game
    ~Game();      // TODO: Destructor to clean up resources
    void start(); // Begin the reversi game

private:
    Board board;
    Player playerA;
    Player playerB;
    Player *currentPlayer;

    bool isGameOver();
    void switchTurn();
    void countPieces();
    void displayWinner();
    void checkAllPossibleMoves();
};

#endif // Game_H