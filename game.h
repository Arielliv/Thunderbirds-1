#pragma once
#include "board.h"
#include "ship.h"
#include "keys.h"
#include <iostream>
#include "ioUtils.h"
#include "menu.h"
#include "gameFile.h"

class Game
{
	Board gameBoard;
	Menu menu;
	int lives = 3;
	GameFile fileGame;
private:
	void printExit() const;
	void printWin() const;
	void printLoss() const;
	void handleFileGame(bool isByFileName);
	std::string getFileName();
public:
	void start();
};

