#pragma once

#include "color.h"
#include "point.h"

enum class ShipSize{ Small = 2, Big=4 };

class Ship
{
	ShipSize shipSize;
	Point startPoint = Point(1,1);
	char figure;
	Color color;
	Direction direction = Direction::Right;
	Point* body;
public:
	Ship(ShipSize shipSize, char figure, Color color, Point startPoint);
	void setDirection(Direction _direction);
	Direction getDirection();
	// get first left point of ship
	Point getCurrentShipPoint();
	const Point* getCurrentBodyPoints() const;
	void move();
	void draw();
	void erase();
	Ship& operator=(const Ship& s);
	~Ship();
};

