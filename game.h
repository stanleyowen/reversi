#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	Board& getBoard();

	void start();
	void setCurrentPlayerColor(char color);
	void switchTurn();
	void toggleShowHints();
	void reset();

	bool move(int x, int y, char color);
	bool isValidMove(int row, int col, char color) const;
	bool isGameOver();

	int getCurrentPlayerPossibleMovesCount() const;
	char getCurrentPlayerColor() const;

	std::vector<std::vector<int>> getCurrentPlayerPossibleMoves();
	std::vector<std::pair<int, int>> getValidMoves(char color) const;

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