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
	Board presetBoard;
	Board gameBoard;
	Menu menu;
	int lives = 3;
	GameFile fileGame;
private:
	bool handleFileGame(bool isWithColor, int fileNumber);
public:
	void start();
};

