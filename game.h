#pragma once
#include "ship.h"
#include "keys.h"
#include "board.h"

class Game
{
	Ship bigShip;
	Ship smallShip;
	Board gameBoard;
public:
	Game():bigShip(Ship(ShipSize::Big, '@', Color::LIGHTCYAN, Point(34,3))), smallShip(Ship(ShipSize::Small, '&', Color::LIGHTMAGENTA, Point(5,5))){}
	void start();
};

