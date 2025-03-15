#include "board.h"
#include <iostream>

Board::Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = ' ';
        }
    }
    board[3][3] = board[4][4] = 'W';
    board[3][4] = board[4][3] = 'B';
}

void Board::display() {
    std::cout << "  0 1 2 3 4 5 6 7" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 8; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Board::move(int x, int y, char color) {
    if (x < 0 || x >= 8 || y < 0 || y >= 8 || board[x][y] != ' ') {
        return false;
    }
    board[x][y] = color;
    flip(x, y, color);
    return true;
}

void Board::flip(int x, int y, char color) {
}