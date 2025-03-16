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

bool Board::move(int x, int y, char color)
{
    if (x < 0 || x >= 8 || y < 0 || y >= 8 || board[y][x] != ' ')
    {
        return false;
    }

    board[y][x] = color;

    flip(x, y, color);

    return true;
}

void Board::flip(int x, int y, char color)
{
    char opponentColor = (color == 'W') ? 'B' : 'W';

    // Check up direction
    for (int i = y - 1; i >= 0; i--)
    {
        if (board[i][x] == color)
        {
            for (int j = y - 1; j > i; j--)
            {
                board[j][x] = color;
            }
            break;
        }
        else if (board[i][x] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check down direction
    for (int i = y + 1; i < 8; i++)
    {
        if (board[i][x] == color)
        {
            for (int j = y + 1; j < i; j++)
            {
                board[j][x] = color;
            }
            break;
        }
        else if (board[i][x] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check left direction
    for (int i = x - 1; i >= 0; i--)
    {
        if (board[y][i] == color)
        {
            for (int j = x - 1; j > i; j--)
            {
                board[y][j] = color;
            }
            break;
        }
        else if (board[y][i] == BOARD_SPACE)
        {
            break;
        }
    }

    // Check right direction
    for (int i = x + 1; i < 8; i++)
    {
        if (board[y][i] == color)
        {
            for (int j = x + 1; j < i; j++)
            {
                board[y][j] = color;
            }
            break;
        }
        else if (board[y][i] == BOARD_SPACE)
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
        std::cout << "Checking up-left direction: " << tempX << " " << tempY << " " << board[tempY][tempX] << std::endl;
        if (tempX < 0 || tempY < 0)
        {
            break;
        }
        if (board[tempY][tempX] == color)
        {
            while (tempX < 8 && tempY < 8)
            {
                tempX++;
                tempY++;

                std::cout << "Checking up-left direction: " << tempX << " " << tempY << std::endl;

                // Stop if we reach the same color
                if (board[tempY][tempX] == color)
                {
                    break;
                }
                // Flip the opponent color during the way back
                board[tempY][tempX] = color;
            }

            break;
        }
        else if (board[tempY][tempX] == BOARD_SPACE)
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
        if (board[tempY][tempX] == color)
        {
            std::cout << "Found the same color!" << std::endl;
            while (tempX >= 0 && tempY < 8)
            {
                tempX--;
                tempY++;

                std::cout << "Checking up-right direction: " << tempX << " " << tempY << std::endl;
                // Stop if we reach the same color
                if (board[tempY][tempX] == color)
                {
                    break;
                }
                // Flip the opponent color during the way back
                board[tempY][tempX] = color;
            }

            break;
        }
        else if (board[tempY][tempX] == BOARD_SPACE)
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
        if (board[tempY][tempX] == color)
        {
            while (tempX < 8 && tempY >= 0)
            {
                tempX++;
                tempY--;

                // Stop if we reach the same color
                if (board[tempY][tempX] == color)
                {
                    break;
                }
                // Flip the opponent color during the way back
                board[tempY][tempX] = color;
            }

            break;
        }
        else if (board[tempY][tempX] == BOARD_SPACE)
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
        if (board[tempY][tempX] == color)
        {
            while (tempX >= 0 && tempY >= 0)
            {
                tempX--;
                tempY--;

                // Stop if we reach the same color
                if (board[tempY][tempX] == color)
                {
                    break;
                }
                // Flip the opponent color during the way back
                board[tempY][tempX] = color;
            }

            break;
        }
        else if (board[tempY][tempX] == BOARD_SPACE)
        {
            break;
        }
    }

    std::cout << "Flipping completed!" << std::endl;
}