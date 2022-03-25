#pragma once
#include "ship.h"
#include "keys.h"
#include "board.h"
#include <iostream>
#include "ioUtils.h"

class Game
{
	Board gameBoard;
	int lives = 3;
public:
	void start();
	void printWin();
	void printLoss();
};

