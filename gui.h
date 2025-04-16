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
	// Graphic rendering functions
	void processEvents();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	// Save/Load file functions
	void saveToFile();
	void loadFromFile();

	// Hint system
	void checkHints();
	void clearHints();
	void updateHintButtonLabel();

	// Game over functions
	void displayWinner();
	void resetGame();

	Game game;
	sf::RenderWindow window;
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

	sf::Text timerText;
	sf::Clock turnClock;
	float turnTimeLimit;

	sf::RectangleShape loadButton;
	sf::Text loadButtonText;

	bool showHints;
	sf::RectangleShape hintToggleButton;
	sf::Text hintToggleButtonText;

	bool askPlayAgain();
	bool showPopup;
	sf::RectangleShape popupBox;
	sf::Text popupText;
	sf::RectangleShape yesButton, noButton;
	sf::Text yesText, noText;
};

#endif // GUI_H