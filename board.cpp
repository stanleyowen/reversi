#include "Board.h"
#include <iostream>
#define BOARD_SPACE ' '

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = BOARD_SPACE;
        }
    }

    board[3][3] = board[4][4] = 'W';
    board[3][4] = board[4][3] = 'B';
}

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

bool Board::move(int x, int y, char color, bool isTest)
{
    if (x < 0 || x >= 8 || y < 0 || y >= 8 || board[y][x] != ' ')
    {
        return false;
    }
    return flip(x, y, color, isTest);
}

// Function to flip the opponent's pieces
// Returns true if any pieces were flipped, false otherwise
bool Board::flip(int x, int y, char color, bool isTest)
{
    // Create a copy of the board to avoid modifying the original during the check
    char tempBoard[8][8];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tempBoard[i][j] = board[i][j];
        }
    }
    tempBoard[y][x] = color;

    char opponentColor = (color == 'W') ? 'B' : 'W';
    int flipCount = 0;

    // Check up direction
    for (int i = y - 1; i >= 0; i--)
    {
        if (tempBoard[i][x] == color)
        {
            for (int j = y - 1; j > i; j--)
            {
                tempBoard[j][x] = color;
                flipCount++;
            }
            break;
        }
        else if (tempBoard[i][x] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check down direction
    for (int i = y + 1; i < 8; i++)
    {
        if (tempBoard[i][x] == color)
        {
            for (int j = y + 1; j < i; j++)
            {
                tempBoard[j][x] = color;
                flipCount++;
            }
            break;
        }
        else if (tempBoard[i][x] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check left direction
    for (int i = x - 1; i >= 0; i--)
    {
        if (tempBoard[y][i] == color)
        {
            for (int j = x - 1; j > i; j--)
            {
                tempBoard[y][j] = color;
                flipCount++;
            }
            break;
        }
        else if (tempBoard[y][i] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check right direction
    for (int i = x + 1; i < 8; i++)
    {
        if (tempBoard[y][i] == color)
        {
            for (int j = x + 1; j < i; j++)
            {
                tempBoard[y][j] = color;
                flipCount++;
            }
            break;
        }
        else if (tempBoard[y][i] == BOARD_SPACE)
        {
            break;
        }
    }

    // Diagonal check
    // Check up-left direction

    // Copy the current x and y to avoid changing the original values
    int tempX = x;
    int tempY = y;

    while (true)
    {
        tempX--;
        tempY--;
        if (tempX < 0 || tempY < 0)
        {
            break;
        }
        if (tempBoard[tempY][tempX] == color)
        {
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
        else if (tempBoard[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    tempX = x;
    tempY = y;

    // Check up-right direction
    while (true)
    {
        tempX++;
        tempY--;
        if (tempX >= 8 || tempY < 0)
        {
            break;
        }
        if (tempBoard[tempY][tempX] == color)
        {
            std::cout << "tempX: " << tempX << ", tempY: " << tempY << std::endl;
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
        else if (tempBoard[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    tempX = x;
    tempY = y;

    // Check down-left direction
    while (true)
    {
        tempX--;
        tempY++;
        if (tempX < 0 || tempY >= 8)
        {
            break;
        }
        if (tempBoard[tempY][tempX] == color)
        {
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
        else if (tempBoard[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    // Copy the current x and y to avoid changing the original values
    tempX = x;
    tempY = y;

    // Check down-right direction
    while (true)
    {
        tempX++;
        tempY++;
        if (tempX >= 8 || tempY >= 8)
        {
            break;
        }
        if (tempBoard[tempY][tempX] == color)
        {
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
            // Otherwise, update the board with the flipped pieces
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (tempBoard[i][j] != board[i][j])
                    {
                        board[i][j] = tempBoard[i][j];
                    }
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