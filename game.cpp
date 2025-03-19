#include "Game.h"
#include <iostream>

// Initialize the players by default settings:
// Player A is 'B' and Player B is 'W'
// Player A has the first turn
Game::Game() : playerA('B'), playerB('W'), currentPlayer(&playerA)
{
}

// Destructor to clean up resources if needed
Game::~Game()
{
}

// Start the reversi game
void Game::start()
{
    // Check if the game is over throughout the game
    while (!isGameOver())
    {
        int posX, posY;

        board.display();         // Display the current board state
        checkAllPossibleMoves(); // Check all possible moves for the current player

        std::cout << "Current Player: " << currentPlayer->getColor() << "\n";
        std::cout << "Possible Moves: ";
        currentPlayer->displayPossibleMoves();
        std::cout << "\n";
        std::cout << "Input move (column and row repsectively): ";
        std::cin >> posX >> posY; // Get the move from the user

        // Try to make a move
        // If the move is valid, switch the turn to the other player
        // If the move is invalid, prompt the user to try again
        if (board.move(posX, posY, currentPlayer->getColor()))
        {
            switchTurn();
        }
        else
        {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    // If the game is over, display the final board state and the winner
    std::cout << "Game Over!" << std::endl;

    board.display();
    displayWinner();
}

// Check if the game is over by checking if the board is full or if no valid moves are available for both players
// Returns true if the game is over, false otherwise
bool Game::isGameOver()
{
    // Check if there are any valid moves for either player
    // If there is at least one valid move, the game is not over
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

// Check all possible moves for the current player
void Game::checkAllPossibleMoves()
{
    // Clear the previous possible moves for the current player to avoid duplicates
    currentPlayer->clearPossibleMoves();

    // Check all positions on the board for possible moves
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // If the move is valid, add it to the current player's possible moves
            if (board.move(col, row, currentPlayer->getColor(), true))
            {
                currentPlayer->addPossibleMove(col, row);
            }
        }
    }
}

// Count the scores of both players by iterating through the board and counting the pieces' colors
void Game::countPieces()
{
    // TODO: Reset the scores for both players to avoid counting previous scores

    // Iterate through the board and increment the scores based on the pieces' colors
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (board.getBoard(col, row) == playerA.getColor())
            {
                playerA.incrementScore();
            }
            else if (board.getBoard(col, row) == playerB.getColor())
            {
                playerB.incrementScore();
            }
        }
    }
}

// Display the final scores and the winner of the game
void Game::displayWinner()
{
    countPieces(); // Count the pieces

    // Display the final scores for both players
    std::cout << "Final Scores:\n";
    std::cout << "Player A (B) Score: " << playerA.getScore() << "\n";
    std::cout << "Player B (W) Score: " << playerB.getScore() << "\n";

    // Determine the winner based on the scores
    if (playerA.getScore() > playerB.getScore())
    {
        std::cout << "Player A wins!\n";
    }
    else if (playerB.getScore() > playerA.getScore())
    {
        std::cout << "Player B wins!\n";
    }
    else
    {
        std::cout << "It's a tie!\n";
    }
}

// Switch the turn to the other player
void Game::switchTurn()
{
    currentPlayer = (currentPlayer == &playerA) ? &playerB : &playerA;
}
