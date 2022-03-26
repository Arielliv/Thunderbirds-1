#include "game.h"

void Game::start() {
	bool isEsc = false;
	bool isWon = false;
	MenuChoice userChoice = MenuChoice::ShowSettings;

	while (userChoice == MenuChoice::ShowSettings) {
		userChoice = this->menu.openMenu();
	}

	if (userChoice == MenuChoice::Exit) {
		return;
	}

	while (this->lives > 0 && !isWon && !isEsc) {
		this->gameBoard = Board(userChoice == MenuChoice::WithColor);
		isWon = this->gameBoard.play(&isEsc, this->lives);
		if (!isWon) {
			clear_screen();
			this->lives--;
		}
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

void Game::printWin() const {
	clear_screen();
	std::cout << "You won!!!" << std::endl;
}
void Game::printLoss() const {
	clear_screen();
	std::cout << "You loss :(" << std::endl;
}