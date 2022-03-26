#pragma once
#include "ship.h"
#include "keys.h"
#include "board.h"
#include <iostream>
#include "ioUtils.h"
#include "menu.h"

class Game
{
	Board gameBoard;
	Menu menu;
	int lives = 3;
public:
	void start();
	void printWin() const;
	void printLoss() const;
};

