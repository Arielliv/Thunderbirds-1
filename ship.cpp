#include "ship.h"

void ship::setDirection(Direction _direction) {
	direction = _direction;
}

Direction ship::getDirection() {
	return direction;
}

void ship::move(Direction _direction) {
	if (shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			body[i][0].draw(' ');
			body[i][0].move(_direction);
			setTextColor(color);
			body[0][0].draw(figure);
		}
		
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				body[i][j].draw(' ');
				body[i][j].move(_direction);
				setTextColor(color);
				body[i][j].draw(figure);
			}
		}
	}
}

void ship::move() {
	if (shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			body[i][0].draw(' ');
			body[i][0].move(direction);
			setTextColor(color);
			body[0][0].draw(figure);
		}

	}
	else {
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				body[i][j].draw(' ');
				body[i][j].move(direction);
				setTextColor(color);
				body[i][j].draw(figure);
			}
		}
	}
}