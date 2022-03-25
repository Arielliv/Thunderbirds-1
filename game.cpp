#include "game.h"

void Game::start() {
	bool isWon = false;
	while (this->lives > 0 && !isWon) {
		isWon = this->gameBoard.play();
		clear_screen();
		this->lives--;
	}
	if (isWon) {
		this->printWin();
	}
	else {
		this->printLoss();
	}
}

void Game::printWin() {
	clear_screen();
	std::cout << "You won!!!" << std::endl;
}
void Game::printLoss() {
	clear_screen();
	std::cout << "You loss :(" << std::endl;
}