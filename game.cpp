#include "Game.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h> 

// Player A has the first turn
Game::Game() : playerA('B'), playerB('W'), currentPlayer(&playerA) {}

// Destructor to clean up resources if needed
Game::~Game() {}

clock_t startT, endT;

// Move the mouse to (x, y)
void gotoxy(int x, int y) {
	COORD coord = { SHORT(x), SHORT(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Countdown function
void countdown(std::atomic<bool>& timeUp, std::atomic<bool>& moveDone) {
	for (int i = 10; i >= 0; --i) {
		if (moveDone) return;
		gotoxy(0, 15);
		std::cout << "Time left: " << i << " seconds   ";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	timeUp = true;
}

std::vector<std::pair<int, int>> Game::getValidMoves(char color) const {
	std::vector<std::pair<int, int>> moves;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (isValidMove(i, j, color)) {
				moves.push_back({ i, j });
			}
		}
	}
	return moves;
}

// Start the Reversi game
void start(bool showHints) {
	std::string fileName;
	char option;
	std::cout << "Do you want to (N)ew game or (L)oad game? ";
	std::cin >> option;

	if (option == 'L' || option == 'l') {
		std::cout << "Enter the file name to load: ";
		std::cin >> fileName;
		std::ifstream inputFile(fileName);
		if (!inputFile) {
			std::cerr << "Error: Could not open file " << fileName << std::endl;
			return;
		}

		std::string line;
		int row = 0;
		while (std::getline(inputFile, line) && row < 8) {
			for (int col = 0; col < 8 && col < line.length(); ++col) {
				board.setBoard(row, col, line[col]);
			}
			++row;
		}
		std::getline(inputFile, line);
		currentPlayer = (line[0] == 'B') ? &player1 : &player2;
		inputFile.close();
	}

	srand(static_cast<unsigned int>(time(nullptr)));

	while (!board.getValidMoves('B').empty() || !board.getValidMoves('W').empty()) {
		board.toggleShowHints(); // Enable hint display if showHints is true
		board.display();

		std::cout << "Current Player: " << currentPlayer->getSymbol() << std::endl;

		auto validMoves = board.getValidMoves(currentPlayer->getSymbol());
		if (validMoves.empty()) {
			std::cout << "No valid moves for " << currentPlayer->getSymbol() << ". Skipping turn.\n";
			switchPlayer();
			continue;
		}

		std::atomic<bool> timeUp(false);
		std::atomic<bool> moveDone(false);
		std::thread timerThread(countdown, std::ref(timeUp), std::ref(moveDone));
		timerThread.detach();

		int posX = -1, posY = -1;
		bool validInput = false;

		while (!timeUp && !moveDone) {
			if (_kbhit()) {
				std::cout << "Enter position (row col): ";
				std::cin >> posY >> posX; // Row first (Y), then Col (X)

				if (board.move(posX, posY, currentPlayer->getSymbol())) {
					moveDone = true;
					validInput = true;
				}
				else {
					std::cout << "Invalid move. Try again.\n";
				}
			}
		}

		if (timeUp && !moveDone) {
			std::cout << "\nTime's up! Performing automatic move...\n";
			auto randomMove = validMoves[rand() % validMoves.size()];
			board.move(randomMove.first, randomMove.second, currentPlayer->getSymbol());
		}

		switchTurn();
	}

	board.display();
	std::cout << "Game Over!\n";

	char saveOption;
	std::cout << "Do you want to save the game? (Y/N): ";
	std::cin >> saveOption;

	if (saveOption == 'Y' || saveOption == 'y') {
		std::cout << "Enter the file name to save: ";
		std::cin >> fileName;
		std::ofstream outputFile(fileName);
		if (!outputFile) {
			std::cerr << "Error: Could not open file " << fileName << std::endl;
			return;
		}

		char boardState[8][8];
		board.getBoard(boardState);
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				outputFile << boardState[row][col];
			}
			outputFile << '\n';
		}

		outputFile << currentPlayer->getSymbol();
		outputFile.close();
		std::cout << "Game saved successfully!\n";
	}
}

Board& Game::getBoard() {
	return board;
}

bool Game::move(int x, int y, char color) {
	return board.move(x, y, color);
}

char Game::getCurrentPlayerColor() const {
	return currentPlayer->getColor();
}

bool Game::isGameOver() {
	checkAllPossibleMoves();

	if (currentPlayer->getPossibleMovesCount() == 0) {
		switchTurn();
		checkAllPossibleMoves();

		if (currentPlayer->getPossibleMovesCount() == 0) {
			return true;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board.move(j, i, playerA.getColor(), true) || board.move(j, i, playerB.getColor(), true)) {
				return false;
			}
		}
	}

	return true;
}

void Game::checkAllPossibleMoves() {
	currentPlayer->clearPossibleMoves();

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (board.move(col, row, currentPlayer->getColor(), true)) {
				currentPlayer->addPossibleMove(col, row);
			}
		}
	}
}

void Game::countPieces() {
	playerA.resetScore(); // Reset scores to avoid counting previous scores
	playerB.resetScore();

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (board.getBoard(col, row) == playerA.getColor()) {
				playerA.incrementScore();
			}
			else if (board.getBoard(col, row) == playerB.getColor()) {
				playerB.incrementScore();
			}
		}
	}
}

void Game::displayWinner() {
	countPieces();

	std::cout << "Final Scores:\n";
	std::cout << "Player A (B) Score: " << playerA.getScore() << "\n";
	std::cout << "Player B (W) Score: " << playerB.getScore() << "\n";

	if (playerA.getScore() > playerB.getScore()) {
		std::cout << "Player A wins!\n";
	}
	else if (playerB.getScore() > playerA.getScore()) {
		std::cout << "Player B wins!\n";
	}
	else {
		std::cout << "It's a tie!\n";
	}
}

void Game::switchTurn() {
	currentPlayer = (currentPlayer == &playerA) ? &playerB : &playerA;
}

bool Game::isValidMove(int row, int col, char color) const {
	// If already occupied, can't move
	if (board.getBoard(row, col) != '.') return false;

	// Determine opponent's color
	char opponent = (color == 'B') ? 'W' : 'B';

	// All 8 directions
	const int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	const int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

	for (int dir = 0; dir < 8; ++dir) {
		int x = row + dx[dir];
		int y = col + dy[dir];
		bool foundOpponent = false;

		// Step in this direction
		while (x >= 0 && x < 8 && y >= 0 && y < 8) {
			char current = board.getBoard(x, y);
			if (current == opponent) {
				foundOpponent = true;
			}
			else if (current == color) {
				if (foundOpponent) return true; // Found sandwich
				break;
			}
			else break;

			x += dx[dir];
			y += dy[dir];
		}
	}

	return false;
}

void Game::toggleShowHints()
{
	board.setShowHints(!board.getShowHints());  // Toggle the showHints flag
	board.display();  // Refresh the display to show/hide hints
}

void Game::setCurrentPlayerColor(char color) {
	if (color == playerA.getColor()) {
		currentPlayer = &playerA;
	}
	else if (color == playerB.getColor()) {
		currentPlayer = &playerB;
	}
}