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
        checkAllPossibleMoves();

        int x, y;

        std::cout << "Current Player: " << currentPlayer->getColor() << "\n";
        std::cout << "Possible Moves: ";
        currentPlayer->displayPossibleMoves();
        std::cout << "\n";
        std::cout << "Enter your move (row and column): ";
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
    board.display();
    displayWinner();
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

void Game::checkAllPossibleMoves()
{
    // Clear previous possible moves
    currentPlayer->clearPossibleMoves();

    // Check if there are any possible moves for the current player
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.move(j, i, currentPlayer->getColor(), true))
            {
                currentPlayer->addPossibleMove(j, i);
            }
        }
    }
}

void Game::countPieces()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.getBoard(i, j) == playerA.getColor())
            {
                playerA.incrementScore();
            }
            else if (board.getBoard(i, j) == playerB.getColor())
            {
                playerB.incrementScore();
            }
        }
    }
}

void Game::displayWinner()
{
    countPieces();
    std::cout << "Player A (B) Score: " << playerA.getScore() << std::endl;
    std::cout << "Player B (W) Score: " << playerB.getScore() << std::endl;

    if (playerA.getScore() > playerB.getScore())
    {
        std::cout << "Player A wins!" << std::endl;
    }
    else if (playerB.getScore() > playerA.getScore())
    {
        std::cout << "Player B wins!" << std::endl;
    }
    else
    {
        std::cout << "It's a tie!" << std::endl;
    }
}

void Game::switchTurn()
{
    currentPlayer = (currentPlayer == &playerA) ? &playerB : &playerA;
}
