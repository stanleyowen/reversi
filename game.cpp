#include "Game.h"
#include <windows.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>

// Player A has the first turn
Game::Game() : playerA('B'), playerB('W'), currentPlayer(&playerA) {}

// Destructor to clean up resources if needed
Game::~Game() {}

Board& Game::getBoard()
{
	return board;
}

// Global timing variables
clock_t startT, endT;

// Move the mouse to (x, y)
void gotoxy(int x, int y)
{
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

// Countdown function
void timer()
{
	startT = clock();
	double sum = 10; // Total countdown seconds
	double time = 0.0;
	int flag = 1;

	while (true)
	{
		endT = clock();
		time = static_cast<double>(endT - startT) / 1000;

		if (flag == 1)
		{
			gotoxy(0, 0);
			if (sum < 5)
				std::cout << "00:0" << sum << std::endl;
			else
				std::cout << "00:" << sum << std::endl;
			flag = 0;
		}
		if (time > 1)
		{
			sum--;
			time -= 1;
			flag = 1;
			startT = endT;
		}
		if (sum == 0)
		{
			gotoxy(0, 0);
			std::cout << "00:0" << sum << std::endl;
			std::cout << "Time's up" << std::endl;
			break;
		}
	}
}

// Get all valid moves for the given color
std::vector<std::pair<int, int>> Game::getValidMoves(char color) const
{
	std::vector<std::pair<int, int>> moves;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (isValidMove(i, j, color))
			{
				moves.push_back({ i, j });
			}
		}
	}
	return moves;
}

// Get the current player's color
char Game::getCurrentPlayerColor() const
{
	return currentPlayer->getColor();
}

// Start the Reversi game
void Game::start()
{
	while (!isGameOver())
	{
		std::thread t1(timer); // Use another thread to run timer()
		t1.detach();		   // Let main() and timer() run at the same time

		int posX, posY;

		board.display(); // Pass valid moves to the display function

		std::cout << "Current Player: " << currentPlayer->getColor() << "\n";
		std::cout << "\n";
		std::cout << "Input move (column and row respectively): ";
		std::cin >> posX >> posY; // Get the move from the user

		// Load saved game state
		if (posX == 9 || posY == 9)
		{
			std::ifstream infile("db-reversi.txt");
			if (infile.is_open())
			{
				std::string line;
				int idx = 0;
				while (std::getline(infile, line))
				{
					if (idx < 8)
					{
						for (int j = 0; j < 8; j++)
						{
							board.setBoard(idx, j, line[j]);
						}
					}
					idx++;
					if (idx < 9)
					{
						continue;
					}
					if (line[0] == 'B')
					{
						currentPlayer = &playerA;
					}
					else
					{
						currentPlayer = &playerB;
					}
				}
				infile.close();
			}
			else
			{
				std::cout << "Unable to open the file." << std::endl;
			}
		}

		// Make a move if valid
		if (move(posX, posY, currentPlayer->getColor()))
		{
			switchTurn();

			// Save current game state to file
			std::ofstream outfile("db-reversi.txt");

			if (outfile.is_open())
			{
				for (int i = 0; i < 8; ++i)
				{
					for (int j = 0; j < 8; ++j)
					{
						outfile << board.getBoard(j, i);
					}
					outfile << std::endl;
				}

				outfile << currentPlayer->getColor() << std::endl;
				outfile.close();
				std::cout << "File saved successfully!" << std::endl;
			}
			else
			{
				std::cout << "Failed to open the file." << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid move. Try again." << std::endl;
		}
	}

	std::cout << "Game Over!" << std::endl;

	board.display(); // Pass valid moves to display at the end

	displayWinner();
}

// Execute a move on the board
bool Game::move(int x, int y, char color)
{
	return board.move(x, y, color);
}

// Check if a game is over (no more valid moves can be made)
bool Game::isGameOver()
{
	checkAllPossibleMoves();

	if (currentPlayer->getPossibleMovesCount() == 0)
	{
		switchTurn();
		checkAllPossibleMoves();

		if (currentPlayer->getPossibleMovesCount() == 0)
		{
			return true;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board.move(j, i, playerA.getColor(), true) || board.move(j, i, playerB.getColor(), true))
			{
				return false;
			}
		}
	}

	return true;
}

// Check all valid moves for the current player and store them
void Game::checkAllPossibleMoves()
{
	currentPlayer->clearPossibleMoves();

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (board.move(col, row, currentPlayer->getColor(), true))
			{
				currentPlayer->addPossibleMove(col, row);
			}
		}
	}
}

// Count pieces for both players
void Game::countPieces()
{
	playerA.resetScore();
	playerB.resetScore();

	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			if (board.getBoard(col, row) == playerA.getColor())
			{
				playerA.incrementScore();
			}
			else if (board.getBoard(col, row) == playerB.getColor())
			{
				playerB.incrementScore();
			}
		}
	}
}

// Display the game winner and final scores
void Game::displayWinner()
{
	countPieces();

	std::cout << "Final Scores:\n";
	std::cout << "Player A (B) Score: " << playerA.getScore() << "\n";
	std::cout << "Player B (W) Score: " << playerB.getScore() << "\n";

	if (playerA.getScore() > playerB.getScore())
	{
		std::cout << "Player A wins!\n";
	}
	else if (playerB.getScore() > playerA.getScore())
	{
		std::cout << "Player B wins!\n";
	}
	else
	{
		std::cout << "It's a tie!\n";
	}
}

// Switch turns between player A and B
void Game::switchTurn()
{
	currentPlayer = (currentPlayer == &playerA) ? &playerB : &playerA;
}

// Validate if a move at (row, col) is legal
bool Game::isValidMove(int row, int col, char color) const
{
	// If already occupied, can't move
	if (board.getBoard(row, col) != '.')
		return false;

	// Determine opponent's color
	char opponent = (color == 'B') ? 'W' : 'B';

	// All 8 directions
	const int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	const int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

	for (int dir = 0; dir < 8; ++dir)
	{
		int x = row + dx[dir];
		int y = col + dy[dir];
		bool foundOpponent = false;

		// Step in this direction
		while (x >= 0 && x < 8 && y >= 0 && y < 8)
		{
			char current = board.getBoard(x, y);
			if (current == opponent)
			{
				foundOpponent = true;
			}
			else if (current == color)
			{
				if (foundOpponent)
					return true; // Found sandwich
				break;
			}
			else
				break;

			x += dx[dir];
			y += dy[dir];
		}
	}

	return false;
}

void Game::toggleShowHints()
{
	board.setShowHints(!board.getShowHints()); // Toggle the showHints flag
	board.display();						   // Refresh the display to show/hide hints
}

void Game::setCurrentPlayerColor(char color)
{
	if (color == playerA.getColor())
	{
		currentPlayer = &playerA;
	}
	else if (color == playerB.getColor())
	{
		currentPlayer = &playerB;
	}
}

// Get current player's valid moves
std::vector<std::vector<int>> Game::getCurrentPlayerPossibleMoves()
{
	checkAllPossibleMoves();
	currentPlayer->displayPossibleMoves();
	std::cout << currentPlayer->getPossibleMovesCount() << std::endl;

	return currentPlayer->getPossibleMoves();
}

// Get count of valid moves for current player
int Game::getCurrentPlayerPossibleMovesCount() const
{
	return currentPlayer->getPossibleMovesCount();
}

// Reset the game to initial state
void Game::reset()
{
	board = Board(); // Reset the board (assumes Board() constructor sets up the 4 center pieces)

	playerA.resetScore();
	playerB.resetScore();

	playerA.clearPossibleMoves();
	playerB.clearPossibleMoves();

	currentPlayer = &playerA; // Black always starts first in Reversi

	std::ofstream outfile("db-reversi.txt");
	if (outfile.is_open())
	{
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				outfile << '.'; // Empty board
			}
			outfile << std::endl;
		}

		// Write initial turn
		outfile << currentPlayer->getColor() << std::endl;
		outfile.close();
	}

	std::cout << "Game has been reset." << std::endl;
}