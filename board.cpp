#include "Board.h"
#include <iostream>
#define BOARD_SPACE ' '

// Constructor to initialize the board with empty spaces and set the initial pieces
Board::Board()
{
    // Initialize the board with empty spaces
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = BOARD_SPACE;
        }
    }

    // Set the initial pieces in the center of the board
    board[3][3] = board[4][4] = 'W';
    board[3][4] = board[4][3] = 'B';
}

// Function to display the board
void Board::display()
{
    // Similar to std::system("cls") but work on Linux and Windows
    std::cout << "\033[2J\033[1;1H";
    std::cout << "  0 1 2 3 4 5 6 7" << std::endl;

    for (int i = 0; i < 8; ++i)
    {
        std::cout << i << " ";
        for (int j = 0; j < 8; ++j)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/// @brief Function to make a move on the board
/// @param posX The x-coordinate where the player wants to place their piece
/// @param posY The y-coordinate where the player wants to place their piece
/// @param currentPlayerColor The color of the current player ('B' or 'W')
/// @param isTest Flag to indicate if the move is a test move (default is false) for calculating possible moves
/// @return True if the move is valid and successful, false otherwise
bool Board::move(int posX, int posY, char currentPlayerColor, bool isTest)
{
    // Check if the position is within the valid range and make sure the position is empty
    if (posX < 0 || posX >= 8 || posY < 0 || posY >= 8 || board[posY][posX] != ' ')
    {
        return false;
    }

    // Check if the move is valid by calling the flip function
    return flip(posX, posY, currentPlayerColor, isTest);
}

// Function to flip the opponent's pieces
// Returns true if any pieces were flipped, false otherwise
bool Board::flip(int x, int y, char color, bool isTest)
{
    // Create a copy of the board to avoid modifying the original during the check
    int flipCount = 0;
    char tempBoard[8][8];
    char opponentColor = (color == 'W') ? 'B' : 'W';

    // Copy the current board state to the temporary board
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            tempBoard[row][col] = board[row][col];
        }
    }

    tempBoard[y][x] = color;

    // Check up direction
    for (int i = y - 1; i >= 0; i--)
    {
        // Check if the current position is occupied by its own color
        // If so, flip the pieces in between the current position and the last occupied position
        if (tempBoard[i][x] == color)
        {
            for (int j = y - 1; j > i; j--)
            {
                tempBoard[j][x] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[i][x] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check down direction
    for (int i = y + 1; i < 8; i++)
    {
        // Check if the current position is occupied by its own color
        // If so, flip the pieces in between the current position and the last occupied position
        if (tempBoard[i][x] == color)
        {
            for (int j = y + 1; j < i; j++)
            {
                tempBoard[j][x] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[i][x] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check left direction
    for (int i = x - 1; i >= 0; i--)
    {
        // Check if the current position is occupied by its own color
        // If so, flip the pieces in between the current position and the last occupied position
        if (tempBoard[y][i] == color)
        {
            for (int j = x - 1; j > i; j--)
            {
                tempBoard[y][j] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[y][i] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check right direction
    for (int i = x + 1; i < 8; i++)
    {
        // Check if the current position is occupied by its own color
        // If so, flip the pieces in between the current position and the last occupied position
        if (tempBoard[y][i] == color)
        {
            for (int j = x + 1; j < i; j++)
            {
                tempBoard[y][j] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[y][i] == BOARD_SPACE)
        {
            break;
        }
    }

    // Copy the current x and y to avoid changing the original values
    int tempX = x;
    int tempY = y;

    // Diagonal check
    // Check up-left direction
    while (true)
    {
        tempX--;
        tempY--;

        // Break if out of bounds
        if (tempX < 0 || tempY < 0)
        {
            break;
        }

        // Check if the current position is occupied by its own color
        if (tempBoard[tempY][tempX] == color)
        {
            // Flip the pieces in between the current position and the last occupied position
            while (tempX < 8 && tempY < 8)
            {
                tempX++;
                tempY++;

                // Stop if we reach the same color
                if (tempBoard[tempY][tempX] == color)
                {
                    break;
                }

                // Flip the opponent color during the way back
                tempBoard[tempY][tempX] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    // Reset the tempX and tempY to the original values
    tempX = x;
    tempY = y;

    // Check up-right direction
    while (true)
    {
        tempX++;
        tempY--;

        // Break if out of bounds
        if (tempX >= 8 || tempY < 0)
        {
            break;
        }

        // Check if the current position is occupied by its own color
        if (tempBoard[tempY][tempX] == color)
        {
            // Flip the pieces in between the current position and the last occupied position
            while (tempX >= 0 && tempY < 8)
            {
                tempX--;
                tempY++;

                // Stop if we reach the same color
                if (tempBoard[tempY][tempX] == color)
                {
                    break;
                }

                // Flip the opponent color during the way back
                tempBoard[tempY][tempX] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    // Reset the tempX and tempY to the original values
    tempX = x;
    tempY = y;

    // Check down-left direction
    while (true)
    {
        tempX--;
        tempY++;

        // Break if out of bounds
        if (tempX < 0 || tempY >= 8)
        {
            break;
        }

        // Check if the current position is occupied by its own color
        if (tempBoard[tempY][tempX] == color)
        {
            // Flip the pieces in between the current position and the last occupied position
            while (tempX < 8 && tempY >= 0)
            {
                tempX++;
                tempY--;

                // Stop if we reach the same color
                if (tempBoard[tempY][tempX] == color)
                {
                    break;
                }

                // Flip the opponent color during the way back
                tempBoard[tempY][tempX] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    // Reset the tempX and tempY to the original values
    tempX = x;
    tempY = y;

    // Check down-right direction
    while (true)
    {
        tempX++;
        tempY++;

        // Break if out of bounds
        if (tempX >= 8 || tempY >= 8)
        {
            break;
        }

        // Check if the current position is occupied by its own color
        if (tempBoard[tempY][tempX] == color)
        {
            // Flip the pieces in between the current position and the last occupied position
            while (tempX >= 0 && tempY >= 0)
            {
                tempX--;
                tempY--;

                // Stop if we reach the same color
                if (tempBoard[tempY][tempX] == color)
                {
                    break;
                }

                // Flip the opponent color during the way back
                tempBoard[tempY][tempX] = color;
                flipCount++;
            }

            break;
        }
        // If the current position is empty, break the loop since no pieces can be flipped
        else if (tempBoard[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check if any pieces were flipped
    if (flipCount > 0)
    {
        // Only update the board if not in test mode
        if (!isTest)
        {
            for (int row = 0; row < 8; row++)
            {
                for (int col = 0; col < 8; col++)
                {
                    board[row][col] = tempBoard[row][col];
                }
            }
        }

        return true;
    }
    // If no pieces were flipped, flag the move as invalid
    else
    {
        return false;
    }
}