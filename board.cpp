#include "Board.h"
#include <iostream>

#define BOARD_SPACE ' '

Board::Board()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			board[i][j] = BOARD_SPACE;

	board[3][3] = board[4][4] = 'W';
	board[3][4] = board[4][3] = 'B';

	showHints = false;
}

void Board::display() const
{
	std::cout << "\033[2J\033[1;1H";
	std::cout << "  0 1 2 3 4 5 6 7\n";

	for (int i = 0; i < 8; ++i)
	{
		std::cout << i << " ";
		for (int j = 0; j < 8; ++j)
		{
			if (board[i][j] == BOARD_SPACE)
			{
				if (isValidMove(j, i, 'B') || isValidMove(j, i, 'W'))
					std::cout << ". ";
				else
					std::cout << BOARD_SPACE << " ";
			}
			else
			{
				std::cout << board[i][j] << " ";
			}
		}
		std::cout << "\n";
	}
}

bool Board::move(int posX, int posY, char currentPlayerColor, bool isTest)
{
	if (posX < 0 || posX >= 8 || posY < 0 || posY >= 8 || board[posY][posX] != BOARD_SPACE)
		return false;

	return flip(posX, posY, currentPlayerColor, isTest);
}

bool Board::flip(int x, int y, char color, bool isTest)
{
	// Create a copy of the board to avoid modifying the original during the check
	int flipCount = 0;
	char tempBoard[8][8];
	char opponentColor = (color == 'W') ? 'B' : 'W';

	// Copy the current board state to the temporary board
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			tempBoard[row][col] = board[row][col];
		}
	}

	tempBoard[y][x] = color;

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

	int tempX = x;
	int tempY = y;

	// Diagonal check (up-left)
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

				if (tempBoard[tempY][tempX] == color)
				{
					break;
				}

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
			while (tempX >= 0 && tempY < 8)
			{
				tempX--;
				tempY++;

				if (tempBoard[tempY][tempX] == color)
				{
					break;
				}

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

				if (tempBoard[tempY][tempX] == color)
				{
					break;
				}

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

				if (tempBoard[tempY][tempX] == color)
				{
					break;
				}

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
		if (!isTest)
		{
			for (int row = 0; row < 8; row++)
			{
				for (int col = 0; col < 8; col++)
				{
					board[row][col] = tempBoard[row][col];
				}
			}
		}
		return true;
	}
	return false;
}

void Board::toggleShowHints()
{
	showHints = !showHints;
}

std::vector<std::pair<int, int>> Board::getValidMoves(char currentPlayerColor) const
{
	std::vector<std::pair<int, int>> validMoves;

	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			if (board[y][x] == BOARD_SPACE && isValidMove(x, y, currentPlayerColor))
			{
				validMoves.emplace_back(x, y);
			}
		}
	}

	return validMoves;
}

bool Board::isValidMove(int x, int y, char color) const
{
	if (x < 0 || x >= 8 || y < 0 || y >= 8 || board[y][x] != BOARD_SPACE)
		return false;

	const int directions[8][2] = {
		{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

	char opponentColor = (color == 'W') ? 'B' : 'W';

	for (auto &dir : directions)
	{
		int dx = dir[1], dy = dir[0];
		int nx = x + dx, ny = y + dy;
		bool foundOpponent = false;

		while (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
		{
			if (board[ny][nx] == opponentColor)
			{
				foundOpponent = true;
			}
			else if (board[ny][nx] == color && foundOpponent)
			{
				return true;
			}
			else
			{
				break;
			}
			nx += dx;
			ny += dy;
		}
	}

	return false;
}

void Board::setBoard(char newBoard[8][8])
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			board[i][j] = newBoard[i][j];
}

void Board::setBoard(int row, int col, char value)
{
	if (row >= 0 && row < 8 && col >= 0 && col < 8)
	{
		board[row][col] = value;
	}
}

void Board::getBoard(char outputBoard[8][8]) const
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			outputBoard[i][j] = board[i][j];
}