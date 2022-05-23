#pragma once
#include "board.h"
#include "ship.h"
#include "keys.h"
#include <iostream>
#include "ioUtils.h"
#include "menu.h"
#include "boardFile.h"

class Game
{
	Board presetBoard;
	Board gameBoard;
	Menu menu;
	int lives = 3;
	BoardFile fileGame;
private:
	bool handleFileGame(bool isWithColor, int fileNumber, bool isLoadMode, bool isSaveMode);
public:
	void start(bool isLoadMode = false, bool isSaveMode = false,bool isSilnet = false);
};

