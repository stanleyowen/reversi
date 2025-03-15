#include "game.h"
#include <iostream>

Game::Game() : player1('B'), player2('W') {
}

void Game::start() {
    while (!isGameOver()) {
        board.display();
        switchTurn();
    }
    std::cout << "Game Over!" << std::endl;
}

bool Game::isGameOver() {
    return false;
}

void Game::switchTurn() {
}