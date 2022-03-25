#include "game.h"

void Game::start() {
	bool isEsc = false;
	bool isWon = false;
	while (this->lives > 0 && !isWon && !isEsc) {
		isWon = this->gameBoard.play(&isEsc);
		clear_screen();
		this->lives--;
		this->gameBoard = Board();
	}
	if (!isEsc) {
		if (isWon) {
			this->printWin();
		}
		else {
			this->printLoss();
		}
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