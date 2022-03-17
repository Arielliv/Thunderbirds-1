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
	ship(ShipSize _shipSize, char _figure, Color _color, point _startPoint) : shipSize(_shipSize), figure(_figure), color(_color), startPoint(_startPoint) {
		if (_shipSize == ShipSize::Small) {
			body = new point *[(int)ShipSize::Small];
			// Allocate memory for each pointer
			body[0] = new point[2];
			for (int i = 0; i < 2; i++) {
				body[0][i] = point(startPoint.getXPoint() +i, startPoint.getYPoint());
			}
		}
		else {
			body = new point *[(int)ShipSize::Big];
			// Allocate memory for each pointer
			for (int i = 0; i < 2; i++) {
				body[i] = new point[2];
				for (int j = 0; j < 2; j++)
				{
					/*1,1 2,1 1,2 2,2
					* [1,1][2,1]
					* [1,2][2,2]
					*/
					
					body[i][j] = point(startPoint.getXPoint() + j, startPoint.getYPoint()+i);
				}
			}
		}
		
	}
	
	void setDirection(Direction _direction);
	Direction getDirection();
	void move();
	void draw();
	~ship() {
		for (int i = 0; i < (int)shipSize; i++) {
			delete body[i];
		}
		delete body;
	}
};

