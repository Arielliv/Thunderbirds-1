#pragma once

#include "color.h"
#include "point.h"

enum class ShipSize{ Small = 1, Big=2 };

class ship
{
	ShipSize shipSize;
	point startPoint = point(1,1);
	char figure;
	Color color;
	Direction direction = Direction::Right;
	point** body;
public:
	ship(ShipSize shipSize, char figure, Color color, point startPoint);
	void setDirection(Direction _direction);
	Direction getDirection();
	void move();
	void draw();
	~ship();
};

