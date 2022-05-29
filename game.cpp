#include "game.h"

void Game::start(bool isLoadMode, bool isSaveMode, bool isSilnet, bool isWithColors) {
	bool isEsc = false;
	bool isWon = false;
	bool isByFileName = false;
	bool didReadFile = false;
	int winningCounter = 0;
	MenuChoice userChoice = MenuChoice::ShowSettings;
	if (!isLoadMode) {
		while (userChoice == MenuChoice::ShowSettings) {
			userChoice = this->menu.openMenu();
		}

		if (userChoice == MenuChoice::Exit) {
			this->menu.printExit();
			return;
		}
	}
	else {
		if (isWithColors) {
			userChoice = MenuChoice::WithColor;
		}
		else {
			userChoice = MenuChoice::WithoutColor;
		}
		
	}

	while (this->lives > 0 && winningCounter < 3 && !isEsc) {
		if ((userChoice == MenuChoice::OpenFileByNameWithColor || userChoice == MenuChoice::OpenFileByNameWithoutColor) && !isByFileName) {
			didReadFile = this->handleFileGame(userChoice == MenuChoice::OpenFileByNameWithColor, -1, isLoadMode, isSaveMode, isSilnet);
			isByFileName = true;
			winningCounter = 2;
		}
		else if(userChoice == MenuChoice::WithColor || userChoice == MenuChoice::WithoutColor){
			didReadFile = this->handleFileGame(userChoice == MenuChoice::WithColor, winningCounter, isLoadMode, isSaveMode, isSilnet);
		}

		if (didReadFile) {
			this->gameBoard = this->presetBoard;
			isWon = this->gameBoard.play(isEsc, this->lives);
			if (!isWon && !isEsc) {
				clear_screen();
				this->lives--;
			}
			else if (!isEsc) {
				winningCounter++;
			}
		}
		else {
			userChoice = this->menu.openMenu();
			isByFileName = false;
			winningCounter = 0;
		}
	}

	if (!isEsc && !isSilnet) {
		if (isWon) {
			this->menu.printWin();
		}
		else {
			this->menu.printLoss();
		}
	}
	else {
		this->menu.printExit();
	}
}

bool Game::handleFileGame(bool isWithColor, int fileNumber, bool isLoadMode, bool isSaveMode, bool isSilnet) {
	int time;
	BoardFile fileGame;
	int legendLocation;
	int controlledShip;
	int numOfBlocks;
	int numOfGhosts;
	std::string screenNumber;
	std::string boardGame = "";
	std::string fileName = "";

	if (fileNumber == -1) {
		fileName = this->menu.getFileName();
		screenNumber = fileName.substr(2, 2);
	}
	else {
		screenNumber.append("0").append(std::to_string(fileNumber + 1));
	}

	if (this->fileGame.openFile(fileName, fileNumber)) {
		this->fileGame.readFile(time, controlledShip, boardGame, legendLocation, numOfBlocks, numOfGhosts);
		this->fileGame.closeFile();
		this->presetBoard = Board(isWithColor, time, (BoardCellType)controlledShip, boardGame, legendLocation, numOfBlocks, numOfGhosts, screenNumber, isSaveMode || isLoadMode, isSaveMode, isSilnet);
		return true;
	}
	else {
		gotoxy(25, 20);
		std::cout << "File dosn't exists :(";
		Sleep(1000);
		return false;
	}
}

