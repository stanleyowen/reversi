#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board
{
private:
	char board[8][8];															   // 8x8 board array to store the game state
	bool showHints;																   // Flag to control whether ghost pieces should be shown
	bool isValidMove(int x, int y, char color) const;							   // New helper function

public:
	Board();																	   // Constructor to initialize the board
	void display() const;														   // Display the board for debugging or console output
	void toggleShowHints();														   // Toggle the hint (ghost piece) state
	void setBoard(char newBoard[8][8]);											   // Set the board state
	void setBoard(int row, int col, char value);								   // Set the value of a single cell
	void getBoard(char outputBoard[8][8]) const;								   // Copy out the board state
	void setShowHints(bool value) { showHints = value; }

	char getBoard(int x, int y) const { return board[y][x]; }					   // Access individual cell

	bool move(int posX, int posY, char currentPlayerColor, bool isTest = false);   // Make a move on the board
	bool flip(int x, int y, char color, bool isTest = false);					   // Flip the opponent's pieces
	bool getShowHints() const { return showHints; }

	std::vector<std::pair<int, int>> getValidMoves(char currentPlayerColor) const; // Get valid move positions for ghost pieces
};

#endif // BOARD_H