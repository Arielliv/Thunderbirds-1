#include "ship.h"

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint) : shipSize(shipSize), figure(figure), color(color), startPoint(startPoint) {
	if (shipSize == ShipSize::Small) {
		body = new Point * [(int)ShipSize::Small];
		// Allocate memory for each pointer
		body[0] = new Point[2];
		for (int i = 0; i < 2; i++) {
			body[0][i] = Point(startPoint.getXPoint() + i, startPoint.getYPoint());
		}
	}
	else {
		body = new Point * [(int)ShipSize::Big];
		// Allocate memory for each pointer
		for (int i = 0; i < 2; i++) {
			body[i] = new Point[2];
			for (int j = 0; j < 2; j++)
			{
				body[i][j] = Point(startPoint.getXPoint() + j, startPoint.getYPoint() + i);
			}
		}
	}

}

void Ship::setDirection(Direction _direction) {
	direction = _direction;
}

Direction Ship::getDirection() {
	return direction;
}

void Ship::move() {
	if (shipSize == ShipSize::Small) {
		if (direction == Direction::Left) {
			for (int i = 0; i < 2; i++) {
				body[0][i].draw(' ');
				body[0][i].move(direction);
				setTextColor(color);
				body[0][i].draw(figure);
			}
		}
		else {
			for (int i = 1; i >= 0; i--) {
				body[0][i].draw(' ');
				body[0][i].move(direction);
				setTextColor(color);
				body[0][i].draw(figure);
			}
		}	

	}
	else {
		if (direction == Direction::Up) {
			for (int i = 0; i < 2; i++){
				body[i][1].draw(' ');
				body[i][0].draw(' ');
				body[i][1].move(direction);
				body[i][0].move(direction);
				setTextColor(color);
				body[i][1].draw(figure);
				body[i][0].draw(figure);
			}
		}
		else {
			for (int i = 1; i >= 0; i--)
			{
				body[i][1].draw(' ');
				body[i][0].draw(' ');
				body[i][1].move(direction);
				body[i][0].move(direction);
				setTextColor(color);
				body[i][1].draw(figure);
				body[i][0].draw(figure);
			}
		}
	}
}
                         

void Ship::draw() {
	if (shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			setTextColor(color);
			body[0][i].draw(figure);
			setTextColor(Color::WHITE);
		}

	}
	else {
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				setTextColor(color);
				body[i][j].draw(figure);
				setTextColor(Color::WHITE);
			}
		}
	}
}

Ship::~Ship() {
	for (int i = 0; i < (int)shipSize; i++) {
		delete body[i];
	}
	delete body;
}