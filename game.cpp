#include "game.h"

void Game::start() {
	bool isEsc = false;
	bool isWon = false;
	MenuChoice userChoice = MenuChoice::ShowSettings;

	while (userChoice == MenuChoice::ShowSettings) {
		userChoice = this->menu.openMenu();
	}

	if (userChoice == MenuChoice::Exit) {
		this->printExit();
		return;
	}

	this->handleFileGame(false);

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
	else {
		this->printExit();
	}
}

std::string Game::getFileName() {
	string name;

	std::cout << "Please enter file name: ";
	std::cin >> name;

	return name;
}

void Game::handleFileGame(bool isByFileName) {
	std::string lives, time, controlledShip, boardGame = "";
	int legendLocation;

	if (isByFileName) {
		this->fileGame.openFile(this->getFileName());
	}
	else {
		this->fileGame.openFile("");
	}

	this->fileGame.readFile(lives, time, controlledShip, boardGame, legendLocation);
}

void Game::printExit() const {
	std::string exit =
		"  .d8888b.                         888 888                               88b. \n"
		"d88P  Y88b                        888 888                               'Y88b \n"
		"888    888                        888 888                                 Y88b\n"
		"888         .d88b.   .d88b.   .d88888 88888b.  888  888  .d88b.     d8b    888\n"
		"888  88888 d88''88b d88''88b d88' 888 888 '88b 888  888 d8P  Y8b    Y8P    888\n"
		"888    888 888  888 888  888 888  888 888  888 888  888 88888888          d88P\n"
		"Y88b  d88P Y88..88P Y88..88P Y88b 888 888 d88P Y88b 888 Y8b.        d8b .d88P \n"
		" 'Y8888P88  'Y88P'   'Y88P'   'Y88888 88888P'   'Y88888  'Y8888     Y8P 88P'  \n"
		"                                                   888                        \n"
		"                                              Y8b d88P                        \n"
		"                                                'Y88P'                        \n";
	clear_screen();
	std::cout << exit << std::endl;
}

void Game::printWin() const {
	std::string win =
		" #     #                                                   #   ##   \n"
		"  #   #    ####   #    #      #    #   ####   #    #      ###    #  \n"
		"   # #    #    #  #    #      #    #  #    #  ##   #       #      # \n"
		"    #     #    #  #    #      #    #  #    #  # #  #              # \n"
		"    #     #    #  #    #      # ## #  #    #  #  # #       #      # \n"
		"    #     #    #  #    #      ##  ##  #    #  #   ##      ###    #  \n"
		"    #      ####    ####       #    #   ####   #    #       #   ##   \n";
	clear_screen();
	std::cout << win << std::endl;
}

void Game::printLoss() const {
	std::string loss =
		" #     #                                                          #     ## \n"
		"  #   #    ####   #    #      #        ####    ####   #####      ###   #   \n"
		"   # #    #    #  #    #      #       #    #  #         #         #   #    \n"
		"    #     #    #  #    #      #       #    #   ####     #             #    \n"
		"    #     #    #  #    #      #       #    #       #    #         #   #    \n"
		"    #     #    #  #    #      #       #    #  #    #    #        ###   #   \n"
		"    #      ####    ####       ######   ####    ####     #         #     ## \n";

	clear_screen();
	std::cout << loss << std::endl;
}

