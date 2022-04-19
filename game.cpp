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

	if (userChoice == MenuChoice::OpenFileByNameWithColor || userChoice == MenuChoice::OpenFileByNameWithoutColor) {
		this->handleFileGameWithName(userChoice == MenuChoice::OpenFileByNameWithColor);
	}

	while (this->lives > 0 && !isWon && !isEsc) {
		this->handleFileGameWithoutName(userChoice == MenuChoice::WithColor);
		this->gameBoard = this->presetBoard;
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

void Game::handleFileGameWithName(bool isWithColor) {
	int time;
	GameFile fileGame;
	int legendLocation;
	int controlledShip;
	int numOfBlocks;
	std::string boardGame = "";
	this->fileGame.openFile(this->getFileName());
	this->fileGame.readFile(this->lives, time, controlledShip, boardGame, legendLocation, numOfBlocks);
	this->presetBoard = Board(isWithColor, time, (BoardCellType)controlledShip, boardGame, legendLocation, numOfBlocks);
}

void Game::handleFileGameWithoutName(bool isWithColor) {
	int time;
	GameFile fileGame;
	int legendLocation;
	int controlledShip;
	int numOfBlocks;
	std::string boardGame = "";
	this->fileGame.openFile("");

	this->fileGame.readFile(this->lives, time, controlledShip, boardGame, legendLocation, numOfBlocks);
	this->presetBoard = Board(isWithColor,time,(BoardCellType)controlledShip,boardGame, legendLocation,numOfBlocks);
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

