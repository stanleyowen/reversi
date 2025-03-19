#ifndef Board_H
#define Board_H

class Board
{
public:
    Board();
    void display();
    bool move(int x, int y, char color, bool isTest = false);
    char getBoard(int x, int y) const { return board[y][x]; }

private:
    char board[8][8];
    bool flip(int x, int y, char color, bool isTest = false);
};

#endif // Board_H