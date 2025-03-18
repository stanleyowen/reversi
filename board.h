#ifndef Board_H
#define Board_H

class Board
{
public:
    Board();
    void display();
    bool move(int x, int y, char color, bool isTest = false);
    char **getBoard() { return (char **)board; };

private:
    char board[8][8];
    bool flip(int x, int y, char color, bool isTest = false);
};

#endif // Board_H