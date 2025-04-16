#include "Player.h"

Player::Player(char color) : color(color), score(0), possibleMovesCount(0)
{
	if (color != 'B' && color != 'W')
	{
		std::cout << "Invalid color. Set to default color 'B'.\n";
		this->color = 'B';
	}

	possibleMoves.resize(64);
	for (int i = 0; i < 64; i++)
	{
		possibleMoves[i].resize(2);
	}
}

void Player::addPossibleMove(int x, int y)
{
	possibleMoves[possibleMovesCount][0] = x;
	possibleMoves[possibleMovesCount][1] = y;
	possibleMovesCount++;
}

void Player::clearPossibleMoves()
{
	possibleMovesCount = 0;
	for (int i = 0; i < 64; i++)
	{
		possibleMoves[i][0] = -1;
		possibleMoves[i][1] = -1;
	}
}

void Player::displayPossibleMoves()
{
	if (possibleMovesCount == 0)
	{
		std::cout << "No possible moves available.\n";
	}
}