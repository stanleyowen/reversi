﻿#include "gui.h"
#include "game.h"
#include <fstream>

void GUI::animatePiecePlacement(int x, int y, sf::Color color)
{
	sf::CircleShape animatedPiece(35); // Start with the same size as the pieces
	animatedPiece.setFillColor(color);

	// Set the position of the animated piece to the center of the square
	sf::Vector2f piecePosition = pieces[x][y].getPosition();
	animatedPiece.setPosition(piecePosition);

	// Set the origin of the animated piece to its center
	animatedPiece.setOrigin(animatedPiece.getRadius(), animatedPiece.getRadius());

	// Adjust the position to account for the origin shift
	animatedPiece.setPosition(piecePosition.x + animatedPiece.getRadius(), piecePosition.y + animatedPiece.getRadius());

	float scale = 0.1f;					// Start with a small scale
	const float maxScale = 1.0f;		// Target scale
	const float animationSpeed = 0.05f; // Speed of the animation (adjusted for 0.05s duration)
	const int frameDelay = 5;			// Delay in milliseconds for smoother animation

	// Calculate the number of frames for the animation
	int totalFrames = static_cast<int>((maxScale - scale) / animationSpeed);

	for (int frame = 0; frame < totalFrames; ++frame)
	{
		sf::sleep(sf::milliseconds(frameDelay)); // Add a small delay for smoother animation

		scale += animationSpeed; // Gradually increase the scale
		animatedPiece.setScale(scale, scale);

		// Redraw only the animated piece on top of the current frame
		window.draw(animatedPiece);
		window.display();
	}

	// Set the final piece color after the animation
	pieces[x][y].setFillColor(color);
}

// Constructor initializes window, fonts, buttons, and board layout
GUI::GUI() : window(sf::VideoMode(1000, 1000), "Reversi"), blackScore(0), whiteScore(0), turnTimeLimit(21.0f), showHints(true)
{
	if (!font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Error: Font not found!";
	}

	// For centering elements
	const float centerX = window.getSize().x / 2.0f;

	// Title
	titleText.setFont(font);
	titleText.setCharacterSize(48);
	titleText.setFillColor(sf::Color::White);
	titleText.setString("Reversi");
	titleText.setPosition(centerX - titleText.getLocalBounds().width / 2, 20);

	// Turn info
	turnText.setFont(font);
	turnText.setCharacterSize(24);
	turnText.setFillColor(sf::Color::White);
	turnText.setPosition(centerX - 100, 90);

	// Score
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(centerX - 100, 800);

	// Timer
	timerText.setFont(font);
	timerText.setCharacterSize(24);
	timerText.setFillColor(sf::Color::Red);
	timerText.setPosition(centerX - 50, 120);

	turnClock.restart();

	// Load Button
	loadButton.setSize(sf::Vector2f(150, 40));
	loadButton.setFillColor(sf::Color(100, 100, 200));
	loadButton.setPosition(180, 830);

	loadButtonText.setFont(font);
	loadButtonText.setCharacterSize(25);
	loadButtonText.setFillColor(sf::Color::White);
	loadButtonText.setString(" Load");
	loadButtonText.setPosition(loadButton.getPosition().x + 40, loadButton.getPosition().y + 5);

	// Hint Toggle Button
	hintToggleButton.setSize(sf::Vector2f(150, 40));
	hintToggleButton.setFillColor(sf::Color(100, 200, 100));
	hintToggleButton.setPosition(380, 830);

	// Set the initial button label based on `showHints`
	updateHintButtonLabel();

	// Board Setup
	sf::Color boardColor(71, 153, 112);
	sf::Color borderColor(34, 77, 56);
	const float boardStartX = (window.getSize().x - 8 * 80) / 2.0f;
	const float boardStartY = 150;

	// Create the board squares and pieces
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			// Board square setup
			boardSquares[i][j].setSize(sf::Vector2f(78, 78));
			boardSquares[i][j].setPosition(boardStartX + i * 80, boardStartY + j * 80);
			boardSquares[i][j].setFillColor(boardColor);
			boardSquares[i][j].setOutlineThickness(2);
			boardSquares[i][j].setOutlineColor(borderColor);

			// Pieces setup
			pieces[i][j].setRadius(35);
			pieces[i][j].setPosition(boardStartX + i * 80 + 5, boardStartY + j * 80 + 5);
			pieces[i][j].setFillColor(sf::Color::Transparent);
		}
	}

	if (showHints)
	{
		checkHints();
	}
}

// Main game loop that keeps the window open
void GUI::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

// Handle mouse clicks and key presses
void GUI::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

			// Check if load button was clicked
			if (loadButton.getGlobalBounds().contains(mousePos))
			{
				loadFromFile();
				turnClock.restart();
			}
			// Check if hint toggle button was clicked
			else if (hintToggleButton.getGlobalBounds().contains(mousePos))
			{
				showHints = !showHints;
				updateHintButtonLabel(); // Update the label when toggling

				if (showHints)
				{
					checkHints(); // If enabled
				}
				else
				{
					clearHints(); // If disabled
				}
			}
			else
			{
				// Check if a valid move was clicked on the board
				const float boardStartX = (window.getSize().x - 8 * 80) / 2.0f;
				const float boardStartY = 150;
				int x = (event.mouseButton.x - boardStartX) / 80;
				int y = (event.mouseButton.y - boardStartY) / 80;

				if (x >= 0 && x < 8 && y >= 0 && y < 8)
				{
					// Get the current player's count of valid moves
					int possibleMovesCount = game.getCurrentPlayerPossibleMovesCount();

					if (possibleMovesCount == 0)
					{
						game.switchTurn(); // Switch turn if no moves available
						turnClock.restart();
					}
					else
					{
						// If move is valid, make move and switch turn
						if (game.move(x, y, game.getCurrentPlayerColor()))
						{
							sf::Color pieceColor = (game.getCurrentPlayerColor() == 'B') ? sf::Color::Black : sf::Color::White;

							// Animate the piece placement
							animatePiecePlacement(x, y, pieceColor);

							saveToFile(); // Save the game state

							// Switch turn to the next player if the game is not over
							game.switchTurn();
							turnClock.restart();
						}
					}
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			// Pressing 'H' will toggle the hints
			if (event.key.code == sf::Keyboard::H)
			{
				showHints = !showHints;	 // Toggle show hint state
				updateHintButtonLabel(); // Update the label when toggling
			}
		}
	}
}

// Update the game state such as timer, scores, etc.
void GUI::update()
{
	float remaining = turnTimeLimit - turnClock.getElapsedTime().asSeconds();

	// If time is up, make a random move for the current player
	if (remaining <= 0)
	{
		std::vector<std::vector<int>> possibleMoves = game.getCurrentPlayerPossibleMoves();
		int possibleMovesCount = game.getCurrentPlayerPossibleMovesCount();

		if (possibleMovesCount != 0)
		{
			int randomIndex = rand() % possibleMovesCount;
			int x = possibleMoves[randomIndex][0];
			int y = possibleMoves[randomIndex][1];

			if (game.move(x, y, game.getCurrentPlayerColor()))
			{
				sf::Color pieceColor = (game.getCurrentPlayerColor() == 'B') ? sf::Color::Black : sf::Color::White;

				// Animate the piece placement
				animatePiecePlacement(x, y, pieceColor);

				saveToFile();
				game.switchTurn();
			}
		}
		else
		{
			game.switchTurn();
		}

		turnClock.restart();
	}

	// Update the timer text
	timerText.setString("Timer: " + std::to_string(static_cast<int>(remaining)));
	blackScore = 0;
	whiteScore = 0;

	// Update pieces and scores
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			char piece = game.getBoard().getBoard(i, j);
			if (piece == 'B')
			{
				pieces[i][j].setFillColor(sf::Color::Black);
				blackScore++;
			}
			else if (piece == 'W')
			{
				pieces[i][j].setFillColor(sf::Color::White);
				whiteScore++;
			}
		}
	}

	// Update texts
	std::string currentPlayer = (game.getCurrentPlayerColor() == 'B') ? "Black" : "White";
	turnText.setString("Turn: " + currentPlayer);
	scoreText.setString("Black: " + std::to_string(blackScore) + " White: " + std::to_string(whiteScore));

	const float centerX = window.getSize().x / 2.0f;
	turnText.setPosition(centerX - turnText.getLocalBounds().width / 2, 80);
	scoreText.setPosition(centerX - scoreText.getLocalBounds().width / 2, 900);
	timerText.setPosition(centerX - timerText.getLocalBounds().width / 2, 120);
}

// Render the board and graphics
void GUI::render()
{
	window.clear(sf::Color(30, 30, 30));
	window.draw(titleText);
	window.draw(turnText);
	window.draw(timerText);

	// Render the board tiles and pieces
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			window.draw(boardSquares[i][j]);
			window.draw(pieces[i][j]); // Render both normal and ghost pieces
		}
	}

	// Draw score display and buttons
	window.draw(scoreText);
	window.draw(loadButton);
	window.draw(loadButtonText);
	window.draw(hintToggleButton);
	window.draw(hintToggleButtonText);
	window.display();

	if (showHints)
	{
		checkHints(); // Update hints if enabled
	}

	// Check if the game is over
	if (game.isGameOver())
	{
		std::cout << "Game over has been called." << std::endl;

		// Show winner in a small popup
		displayWinner();

		// Ask if the player wants to play again after the winner popup is closed
		bool playAgain = askPlayAgain();

		// If yes, reset the game; else, close the window
		if (playAgain)
		{
			resetGame();
		}
		else
		{
			window.close();
		}

		return;
	}
}

// Save the current board state and player turn to a file
void GUI::saveToFile()
{
	std::ofstream outfile("db-reversi.txt");
	if (outfile.is_open())
	{
		// Save each row of the board
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				outfile << game.getBoard().getBoard(j, i); // Column-major format
			}
			outfile << "\n";
		}
		// Save which player's turn it is
		outfile << game.getCurrentPlayerColor() << std::endl;
		outfile.close();
	}
}

// Load in the saved file
void GUI::loadFromFile()
{
	std::ifstream infile("db-reversi.txt");
	if (infile.is_open())
	{
		std::string line;
		int row = 0;
		while (std::getline(infile, line))
		{
			if (row < 8)
			{
				// Load board characters for each cell
				for (int col = 0; col < 8 && col < line.size(); ++col)
				{
					game.getBoard().setBoard(row, col, line[col]);
				}
			}
			else if (row == 8 && !line.empty())
			{
				// Load player's turn
				game.setCurrentPlayerColor(line[0]);
			}
			row++;
		}
		infile.close();
	}
}

// Get the possible moves and show it on the board
void GUI::checkHints()
{
	clearHints();

	// Get valid moves for the current player
	std::vector<std::vector<int>> possibleMoves = game.getCurrentPlayerPossibleMoves();

	for (const auto& move : possibleMoves)
	{
		// Ensure move is inside bounds
		int x = move[0], y = move[1];

		if (x >= 0 && x < 8 && y >= 0 && y < 8)
		{
			// Show hint pieces
			if (game.getCurrentPlayerColor() == 'B')
			{
				pieces[x][y].setFillColor(sf::Color(0, 0, 0, 100)); // translucent black
			}
			else
			{
				pieces[x][y].setFillColor(sf::Color(255, 255, 255, 100)); // translucent white
			}
		}
	}
}

// Clear all hint pieces from board
void GUI::clearHints()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			pieces[i][j].setFillColor(sf::Color::Transparent);
		}
	}
}

void GUI::updateHintButtonLabel()
{
	// Update hint toggle button label and center it
	hintToggleButtonText.setFont(font);
	hintToggleButtonText.setCharacterSize(25);
	hintToggleButtonText.setString(showHints ? "Hints: ON" : "Hints: OFF");

	// Recenter the text on the button
	float textX = hintToggleButton.getPosition().x + (hintToggleButton.getSize().x - hintToggleButtonText.getLocalBounds().width) / 2;
	float textY = hintToggleButton.getPosition().y + (hintToggleButton.getSize().y - hintToggleButtonText.getLocalBounds().height) / 2 - 5;
	hintToggleButtonText.setPosition(textX, textY);
}

bool GUI::askPlayAgain()
{
	// Open a new mini window asking the user if they want to play again
	sf::RenderWindow popup(sf::VideoMode(400, 200), "Game Over");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return false;
	}

	// Create question and buttons
	sf::Text question("Do you want to play again?", font, 20);
	question.setFillColor(sf::Color::White);
	question.setPosition(50, 50);

	sf::RectangleShape yesButton(sf::Vector2f(100, 40));
	yesButton.setFillColor(sf::Color::Green);
	yesButton.setPosition(50, 120);

	sf::Text yesText("Yes", font, 20);
	yesText.setFillColor(sf::Color::Black);
	yesText.setPosition(75, 125);

	sf::RectangleShape noButton(sf::Vector2f(100, 40));
	noButton.setFillColor(sf::Color::Red);
	noButton.setPosition(250, 120);

	sf::Text noText("No", font, 20);
	noText.setFillColor(sf::Color::Black);
	noText.setPosition(280, 125);

	// Handle user input by mouse clicks
	while (popup.isOpen())
	{
		sf::Event event;
		while (popup.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				popup.close();
				return false;
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
				if (yesButton.getGlobalBounds().contains(mousePos))
				{
					popup.close();
					return true;
				}
				else if (noButton.getGlobalBounds().contains(mousePos))
				{
					popup.close();
					return false;
				}
			}
		}

		popup.clear(sf::Color(30, 30, 30));
		popup.draw(question);
		popup.draw(yesButton);
		popup.draw(yesText);
		popup.draw(noButton);
		popup.draw(noText);
		popup.display();
	}

	return false;
}

void GUI::resetGame()
{
	// Reset game logic and internal clock
	game.reset();
	turnClock.restart();

	// Reset piece colors and hint markers
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			pieces[i][j].setFillColor(sf::Color::Transparent);
			ghostPieces[i][j].setFillColor(sf::Color::Transparent);
		}
	}

	// Reset scores and UI text
	blackScore = 0;
	whiteScore = 0;
	turnText.setString("Turn: Black");
	scoreText.setString("Black: 0 White: 0");
	timerText.setString("Timer: " + std::to_string(static_cast<int>(turnTimeLimit)));

	// Save new empty board state
	saveToFile();

	if (showHints)
	{
		checkHints();
	}
}

void GUI::displayWinner()
{
	// Count pieces
	blackScore = 0;
	whiteScore = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			char piece = game.getBoard().getBoard(i, j);
			if (piece == 'B')
				blackScore++;
			else if (piece == 'W')
				whiteScore++;
		}
	}

	std::string winner;
	if (blackScore > whiteScore)
		winner = "Black wins!";
	else if (whiteScore > blackScore)
		winner = "White wins!";
	else
		winner = "It's a tie!";

	// Create popup window
	sf::RenderWindow popup(sf::VideoMode(400, 250), "Game Over");

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		return;

	// Create result text with scores
	std::string resultMessage = winner + "\n\nBlack: " + std::to_string(blackScore) + "\nWhite: " + std::to_string(whiteScore);
	sf::Text resultText(resultMessage, font, 24);
	resultText.setFillColor(sf::Color::White);

	// Center the result text
	sf::FloatRect textBounds = resultText.getLocalBounds();
	resultText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
	resultText.setPosition(popup.getSize().x / 2, popup.getSize().y / 2);

	// Show popup until user presses a key or closes
	while (popup.isOpen())
	{
		sf::Event event;
		while (popup.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
			{
				popup.close(); // Any interaction closes the popup
			}
		}

		popup.clear(sf::Color(30, 30, 30)); // Dark background
		popup.draw(resultText);
		popup.display();
	}
}