#include "game.h"
#include <iostream>

Game::Game() : player1('B'), player2('W'), currentPlayer(&player1) {
}

void Game::start() {
    while (!isGameOver()) {
        board.display();

        int x, y;

        std::cout << "Player " << currentPlayer->getColor() << ", enter your move (row and column): ";
        std::cin >> x >> y;

        if (board.move(x, y, currentPlayer->getColor())) {
            switchTurn();
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    std::cout << "Game Over!" << std::endl;
}

bool Game::isGameOver() {
    return false;
}

void Game::switchTurn() {
    currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
}