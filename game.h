#pragma once
#include "ship.h"
#include "keys.h"

class Game
{
	ship bigShip;
	ship smallShip;
public:
	Game():bigShip(ship(ShipSize::Big, '@', Color::LIGHTCYAN, point(5,5))), smallShip(ship(ShipSize::Small, '#', Color::LIGHTMAGENTA, point(5,5))){
	
	}
	void start();
};

