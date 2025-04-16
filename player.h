#ifndef Player_H
#define Player_H

#include <vector>
#include <iostream>
#include <string>

class Player
{
private:
	char color;
	int score;
	int possibleMovesCount;
	std::string name;

	// clang-format off
	std::vector<std::vector<int> > possibleMoves;
	// clang-format on

public:
	Player(char color);
	char getColor() const { return color; };
	int getScore() const { return score; };
	void incrementScore() { score++; };
	void resetScore() { score = 0; };
	void setName(const std::string &playerName) { name = playerName; };
	std::string getName() const { return name; };

	void addPossibleMove(int x, int y);
	void clearPossibleMoves();
	void displayPossibleMoves();
	int getPossibleMovesCount() const { return possibleMovesCount; };
	std::vector<std::vector<int>> getPossibleMoves() const
	{
		return possibleMoves;
	};
};

#endif // Player_H