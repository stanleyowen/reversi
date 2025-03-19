#include "Player.h"
#include <iostream>

/// @brief Constructor for the Player class
/// @param color The color of the player ('B' for black, 'W' for white)
Player::Player(char color) : color(color), score(0), possibleMovesCount(0)
{
    // Set the default color to 'B' if the provided color is invalid
    if (color != 'B' && color != 'W')
    {
        std::cout << "Invalid color. Set to default color 'B'.\n";
        this->color = 'B';
    }

    possibleMoves.resize(64); // Initialize with a maximum of 64 possible moves

    for (int i = 0; i < 64; i++)
    {
        possibleMoves[i].resize(2); // Each move has two coordinates (x, y)
    }
}

/// @brief Add a possible move to the player's list of possible moves
/// @param posX The x-coordinate of the possible move
/// @param posY The y-coordinate of the possible move
void Player::addPossibleMove(int posX, int posY)
{
    possibleMoves[possibleMovesCount][0] = posX;
    possibleMoves[possibleMovesCount][1] = posY;
    possibleMovesCount++;
}

/// @brief Clear the list of possible moves for the player
void Player::clearPossibleMoves()
{
    // Reset the possible moves count and clear the list of possible moves
    possibleMovesCount = 0;

    // Reset all possible moves to -1 to indicate they are empty
    for (int i = 0; i < 64; i++)
    {
        possibleMoves[i][0] = -1;
        possibleMoves[i][1] = -1;
    }
}

/// @brief Display the possible moves for the player
void Player::displayPossibleMoves()
{
    // If there are no possible moves, display a message
    // Otherwise, display the list of possible moves
    if (possibleMovesCount == 0)
    {
        std::cout << "No possible moves available.\n";
    }
    else
    {
        std::cout << "Possible moves available: ";

        for (int i = 0; i < possibleMovesCount; i++)
        {
            std::cout << "(" << possibleMoves[i][0] << ", " << possibleMoves[i][1] << ") ";
        }

        std::cout << "\n";
    }
}