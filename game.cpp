#include "Game.h"
#include <iostream>

Game::Game() : playerA('B'), playerB('W'), currentPlayer(&playerA)
{
}

void Game::start()
{
    while (!isGameOver())
    {
        board.display();

        int x, y;

        std::cout << "Player " << currentPlayer->getColor() << ", enter move (row and column): ";
        std::cin >> x >> y;

        if (board.move(x, y, currentPlayer->getColor()))
        {
            switchTurn();
        }
        else
        {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    std::cout << "Game Over!" << std::endl;
}

bool Game::isGameOver()
{
    // Check if the board is full or if no valid moves are available for both players
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.move(j, i, playerA.getColor(), true) || board.move(j, i, playerB.getColor(), true))
            {
                return false;
            }
        }
    }
    return true;
}

void Game::switchTurn()
{
    currentPlayer = (currentPlayer == &playerA) ? &playerB : &playerA;
}
