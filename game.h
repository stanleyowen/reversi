
#include <atomic>
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <vector>
#include <utility>

class Game
{
public:
	Game();
	~Game();

	void start();
	Board& getBoard();
	bool move(int x, int y, char color);
	bool isValidMove(int row, int col, char color) const;
	char getCurrentPlayerColor() const;
	void switchTurn();
	std::vector<std::pair<int, int>> getValidMoves(char color) const;
	void toggleShowHints();
	void setCurrentPlayerColor(char color);
    

private:
	Board board;
	Player playerA;
	Player playerB;
	Player* currentPlayer;

	bool isGameOver();
	void countPieces();
	void displayWinner();
	void checkAllPossibleMoves();
    void timer();
    std::atomic<bool> moveDone = false;
    std::atomic<bool> timeUp = false;
    
};

#endif // GAME_H
