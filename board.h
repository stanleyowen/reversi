#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    Board();
    void display();
    bool move(int x, int y, char color);
private:
    char board[8][8];
    void flip(int x, int y, char color);
};

#endif