#include "gui.h"
#include <fstream>

GUI::GUI() : window(sf::VideoMode(1000, 1000), "Reversi"), blackScore(0), whiteScore(0), turnTimeLimit(10.0f), showHints(true)
{
	if (!font.loadFromFile("Arial.ttf"))
	{
		// Handle font loading error
	}

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
	loadButtonText.setCharacterSize(20);
	loadButtonText.setFillColor(sf::Color::White);
	loadButtonText.setString("Load");
	loadButtonText.setPosition(loadButton.getPosition().x + 40, loadButton.getPosition().y + 5);

	// Hint Toggle Button
	hintToggleButton.setSize(sf::Vector2f(150, 40));
	hintToggleButton.setFillColor(sf::Color(100, 200, 100));
	hintToggleButton.setPosition(380, 830);

	// Set the initial button label based on `showHints`
	updateHintButtonLabel();

	// Board
	sf::Color boardColor(71, 153, 112);
	sf::Color borderColor(34, 77, 56);
	const float boardStartX = (window.getSize().x - 8 * 80) / 2.0f;
	const float boardStartY = 150;

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			boardSquares[i][j].setSize(sf::Vector2f(78, 78));
			boardSquares[i][j].setPosition(boardStartX + i * 80, boardStartY + j * 80);
			boardSquares[i][j].setFillColor(boardColor);
			boardSquares[i][j].setOutlineThickness(2);
			boardSquares[i][j].setOutlineColor(borderColor);

			pieces[i][j].setRadius(35);
			pieces[i][j].setPosition(boardStartX + i * 80 + 5, boardStartY + j * 80 + 5);
			pieces[i][j].setFillColor(sf::Color::Transparent);
		}
	}
}

void GUI::checkHints()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			pieces[i][j].setFillColor(sf::Color::Transparent);

	std::vector<std::vector<int>> possibleMoves = game.getCurrentPlayerPossibleMoves();

	for (const auto &move : possibleMoves)
	{
		int x = move[0];
		int y = move[1];
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

void GUI::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

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
				checkHints();
			}
			else
			{
				const float boardStartX = (window.getSize().x - 8 * 80) / 2.0f;
				const float boardStartY = 150;
				int x = (event.mouseButton.x - boardStartX) / 80;
				int y = (event.mouseButton.y - boardStartY) / 80;

				if (x >= 0 && x < 8 && y >= 0 && y < 8)
				{
					if (game.move(x, y, game.getCurrentPlayerColor()))
					{
						game.switchTurn();
						saveToFile();
						turnClock.restart();

						// Reset all ghost pieces

						// Ghost pieces
						if (showHints)
						{
							checkHints();
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
				showHints = !showHints;
				updateHintButtonLabel(); // Update the label when toggling
			}
		}
	}
}

void GUI::update()
{
	float remaining = turnTimeLimit - turnClock.getElapsedTime().asSeconds();
	if (remaining <= 0)
	{
		// game.checkAllPossibleMoves();
		//// Random move made by the AI
		// std::vector<std::pair<int, int>> validMoves = game.getCurrentPlayerColor();

		// if (!validMoves.empty())
		//{
		//	// Seed random number generator
		//	srand(static_cast<unsigned>(std::time(0)));

		//	// Choose a random move
		//	int randomIndex = rand() % validMoves.size();
		//	int randomX = validMoves[randomIndex].first;
		//	int randomY = validMoves[randomIndex].second;

		//	// Make the random move
		//	game.move(randomX, randomY, game.getCurrentPlayerColor());
		//}
		// else
		//{
		//	std::cout << "No valid moves available for AI." << std::endl;
		//}

		game.switchTurn();
		checkHints();
		turnClock.restart();
	}
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
	scoreText.setString("Black: " + std::to_string(blackScore) + "  White: " + std::to_string(whiteScore));

	const float centerX = window.getSize().x / 2.0f;
	turnText.setPosition(centerX - turnText.getLocalBounds().width / 2, 80);
	scoreText.setPosition(centerX - scoreText.getLocalBounds().width / 2, 900);
	timerText.setPosition(centerX - timerText.getLocalBounds().width / 2, 120);
}

void GUI::render()
{
	window.clear(sf::Color(30, 30, 30));
	window.draw(titleText);
	window.draw(turnText);
	window.draw(timerText);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			window.draw(boardSquares[i][j]);
			window.draw(pieces[i][j]);
		}
	}
	window.draw(scoreText);
	window.draw(loadButton);
	window.draw(loadButtonText);
	window.draw(hintToggleButton);
	window.draw(hintToggleButtonText);
	window.display();
}

void GUI::saveToFile()
{
	std::ofstream outfile("example.txt");
	if (outfile.is_open())
	{
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				outfile << game.getBoard().getBoard(j, i); // column-major
			}
			outfile << "\n";
		}
		outfile << game.getCurrentPlayerColor() << std::endl;
		outfile.close();
	}
}

void GUI::loadFromFile()
{
	std::ifstream infile("example.txt");
	if (infile.is_open())
	{
		std::string line;
		int row = 0;
		while (std::getline(infile, line))
		{
			if (row < 8)
			{
				for (int col = 0; col < 8 && col < line.size(); ++col)
				{
					game.getBoard().setBoard(row, col, line[col]);
				}
			}
			else if (row == 8 && !line.empty())
			{
				game.setCurrentPlayerColor(line[0]);
			}
			row++;
		}
		infile.close();
	}
}

void GUI::updateHintButtonLabel()
{
	std::cout << "Updating hint button label to: " << (showHints ? "Hints: ON" : "Hints: OFF") << std::endl;
	hintToggleButtonText.setFont(font);
	hintToggleButtonText.setString(showHints ? "Hints: ON" : "Hints: OFF");

	// Recenter the text on the button
	float textX = hintToggleButton.getPosition().x + (hintToggleButton.getSize().x - hintToggleButtonText.getLocalBounds().width) / 2;
	float textY = hintToggleButton.getPosition().y + (hintToggleButton.getSize().y - hintToggleButtonText.getLocalBounds().height) / 2 - 5;
	hintToggleButtonText.setPosition(textX, textY);
}
