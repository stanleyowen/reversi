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
    return false;
}

void Game::switchTurn()
{
    currentPlayer = (currentPlayer == &playerA) ? &playerB : &playerA;
}
