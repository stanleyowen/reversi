#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Game.h"

class GUI
{
public:
	GUI();
	void run();

private:
	void processEvents();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void saveToFile();
	void loadFromFile();
	void updateHintButtonLabel();
	void checkHints();
	void clearHints();
	void displayWinner();

	sf::RenderWindow window;
	Game game;
	sf::Font font;
	sf::Text text;
	sf::Text turnText;
	sf::Text scoreText;
	sf::Text player1NameText;
	sf::Text player2NameText;
	sf::Text titleText;
	sf::RectangleShape boardSquares[8][8];
	sf::CircleShape pieces[8][8];
	sf::CircleShape ghostPieces[8][8];
	int blackScore;
	int whiteScore;

	std::vector<sf::CircleShape> animatedPieces;
	std::vector<float> animationScales;
	sf::Clock animationClock;
	bool isAnimating;

	sf::Text timerText;
	sf::Clock turnClock;
	float turnTimeLimit;

	sf::RectangleShape loadButton;
	sf::Text loadButtonText;

	bool showHints;
	sf::RectangleShape hintToggleButton;
	sf::Text hintToggleButtonText;
};

#endif // GUI_H