#pragma once
#include "board.h"
#include "ship.h"
#include "keys.h"
#include <iostream>
#include "ioUtils.h"
#include "menu.h"

class Game
{
	Board gameBoard;
	Menu menu;
	int lives = 3;
private:
	void printExit() const;
	void printWin() const;
	void printLoss() const;
public:
	void start();
};

