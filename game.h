#pragma once
#include "ship.h"
#include "keys.h"

class Game
{
	ship bigShip;
	ship smallShip;
public:
	Game():bigShip(ship(ShipSize::Big, '@', Color::LIGHTCYAN)), smallShip(ship(ShipSize::Small, '#', Color::LIGHTMAGENTA)){
	
	}
	void start();
};

