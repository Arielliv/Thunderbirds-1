#pragma once

#include "color.h"
#include "point.h"

enum class ShipSize{ Small = 1, Big=2 };

class ship
{
	ShipSize shipSize;
	char figure;
	Color color;
	point** body;
public:
	ship(ShipSize _shipSize, char _figure, Color _color, point* _body) : shipSize(_shipSize), figure(_figure), color(_color) {
		if (_shipSize == ShipSize::Small) {
			body = new point * [(int)ShipSize::Small];
		}
		else {
			body = new point * [(int)ShipSize::Big];
		}
		// Allocate memory for each pointer
		for (int i = 0; i < 2; i++) {
			body[i] = (point*)new point[1];
		}
	}
	~ship() {
		for (int i = 0; i < 2; i++) {
			delete body[i];
		}
		delete body;
	}
	void move();
};

