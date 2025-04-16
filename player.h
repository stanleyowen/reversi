#ifndef Player_H
#define Player_H

#include <vector>
#include <iostream>
#include <string>

class Player
{
private:
	// Player's color, scores and count of valid moves
	char color;
	int score;
	int possibleMovesCount;

	std::string name;
	std::vector<std::vector<int> > possibleMoves;

public:
	Player(char color);								// Constructor that initializes the player with a given color

	void addPossibleMove(int x, int y);				// Adds a valid move to the list of possible moves				
	void clearPossibleMoves();						// Clears the list of possible moves
	void displayPossibleMoves();					// Displays the possible moves

	// Getters to retrieve players' info
	char getColor() const { return color; };
	int getScore() const { return score; };
	int getPossibleMovesCount() const { return possibleMovesCount; };

	std::vector<std::vector<int>> getPossibleMoves() const
	{
		return possibleMoves;
	};

	// Score manipulation
	void incrementScore() { score++; };
	void resetScore() { score = 0; };
};

#endif // Player_H