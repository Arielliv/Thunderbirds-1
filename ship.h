#pragma once

#include "color.h"
#include "point.h"
#include <vector>

enum class ShipSize{ Small = 2, Big=4 };

class Ship
{
	ShipSize shipSize;
	Point startPoint = Point(1,1);
	char figure;
	Color color;
	Direction direction = Direction::Right;
	vector<Point> body;
	bool isWithColors = false;
public:
	Ship(ShipSize shipSize, char figure, Color color, Point startPoint, bool isWithColors);
	void setDirection(const Direction _direction);
	Direction getDirection() const;
	Point getCurrentShipPoint() const;
	const vector<Point> getCurrentBodyPoints() const;
	void move();
	void draw() const;
	void erase() const;
	Ship& operator=(const Ship& s);
	~Ship();
};

