#pragma once

#include "color.h"
#include "point.h"

enum class ShipSize{ Small = 1, Big=2 };

class ship
{
	ShipSize shipSize;
	char figure;
	Color color;
	Direction direction = Direction::Right;
	point** body;
public:
	ship(ShipSize _shipSize, char _figure, Color _color) : shipSize(_shipSize), figure(_figure), color(_color) {
		if (_shipSize == ShipSize::Small) {
			body = new point * [(int)ShipSize::Small];
			// Allocate memory for each pointer
			for (int i = 0; i < 2; i++) {
				body[i] = (point*)new point[1];
			}
		}
		else {
			body = new point * [(int)ShipSize::Big];
			// Allocate memory for each pointer
			for (int i = 0; i < 2; i++) {
				body[i] = (point*)new point[2];
			}
		}
		
	}
	
	void setDirection(Direction _direction);
	Direction getDirection();
	void move();
	void move(Direction _direction);
	~ship() {
		for (int i = 0; i < 2; i++) {
			delete body[i];
		}
		delete body;
	}
};

