#include "game.h"

void Game::start() {
	bool isEsc = false;
	bool isWon = false;
	bool isByFileName = false;
	int winningCounter = 0;
	MenuChoice userChoice = MenuChoice::ShowSettings;

	while (userChoice == MenuChoice::ShowSettings) {
		userChoice = this->menu.openMenu();
	}

	if (userChoice == MenuChoice::Exit) {
		this->menu.printExit();
		return;
	}

	if (userChoice == MenuChoice::OpenFileByNameWithColor || userChoice == MenuChoice::OpenFileByNameWithoutColor) {
		this->handleFileGameWithName(userChoice == MenuChoice::OpenFileByNameWithColor);
		isByFileName = true;
	}

	while (this->lives > 0 && winningCounter < 3 && !isEsc) {
		if (!isByFileName) {
			this->handleFileGameWithoutName(userChoice == MenuChoice::WithColor, winningCounter);
		}
		else {
			winningCounter = 2;
		}
		this->gameBoard = this->presetBoard;
		isWon = this->gameBoard.play(isEsc, this->lives);
		if (!isWon && !isEsc) {
			clear_screen();
			this->lives--;
		}
		else if(!isEsc) {
			winningCounter++;
		}
	}
	if (!isEsc) {
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

void Game::handleFileGameWithName(bool isWithColor) {
	int time;
	GameFile fileGame;
	int legendLocation;
	int controlledShip;
	int numOfBlocks;
	std::string boardGame = "";
	this->fileGame.openFile(this->menu.getFileName(), -1);
	this->fileGame.readFile(time, controlledShip, boardGame, legendLocation, numOfBlocks);
	this->fileGame.closeFile();
	this->presetBoard = Board(isWithColor, time, (BoardCellType)controlledShip, boardGame, legendLocation, numOfBlocks);
}

void Game::handleFileGameWithoutName(bool isWithColor, int fileNumber) {
	int time;
	GameFile fileGame;
	int legendLocation;
	int controlledShip;
	int numOfBlocks;
	std::string boardGame = "";
	this->fileGame.openFile("", fileNumber);
	this->fileGame.readFile(time, controlledShip, boardGame, legendLocation, numOfBlocks);
	this->fileGame.closeFile();
	this->presetBoard = Board(isWithColor,time,(BoardCellType)controlledShip,boardGame, legendLocation,numOfBlocks);
}

