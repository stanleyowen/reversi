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
	std::vector<std::vector<int>> getCurrentPlayerPossibleMoves();
	int getCurrentPlayerPossibleMovesCount() const;
	bool isGameOver();

private:
	Board board;
	Player playerA;
	Player playerB;
	Player* currentPlayer;

	void countPieces();
	void displayWinner();
	void checkAllPossibleMoves();
};

#endif // GAME_H
