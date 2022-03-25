#include "ship.h"

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint) : shipSize(shipSize), figure(figure), color(color), startPoint(startPoint) {
	if (shipSize == ShipSize::Small) {
		this->body = new Point * [(int)ShipSize::Small];
		// Allocate memory for each pointer
		this->body[0] = new Point[2];
		for (int i = 0; i < 2; i++) {
			this->body[0][i] = Point(this->startPoint.getXPoint() + i, this->startPoint.getYPoint());
		}
	}
	else {
		this->body = new Point * [(int)ShipSize::Big];
		// Allocate memory for each pointer
		for (int i = 0; i < 2; i++) {
			this->body[i] = new Point[2];
			for (int j = 0; j < 2; j++)
			{
				this->body[i][j] = Point(this->startPoint.getXPoint() + j, this->startPoint.getYPoint() + i);
			}
		}
	}
}

void Ship::setDirection(Direction direction) {
	this->direction = direction;
}

Direction Ship::getDirection() {
	return this->direction;
}

void Ship::move() {
	if (this->shipSize == ShipSize::Small) {
		if (this->direction == Direction::Left) {
			for (int i = 0; i < 2; i++) {
				this->body[0][i].draw(' ');
				this->body[0][i].move(direction);
				setTextColor(color);
				this->body[0][i].draw(figure);
			}
		}
		else {
			for (int i = 1; i >= 0; i--) {
				this->body[0][i].draw(' ');
				this->body[0][i].move(direction);
				setTextColor(color);
				this->body[0][i].draw(figure);
			}
		}	

	}
	else {
		if (this->direction == Direction::Up) {
			for (int i = 0; i < 2; i++){
				this->body[i][0].draw(' ');
				this->body[i][1].draw(' ');
				this->body[i][0].move(direction);
				this->body[i][1].move(direction);
				setTextColor(color);
				this->body[i][0].draw(figure);
				this->body[i][1].draw(figure);
			}
		}
		else {
			for (int i = 1; i >= 0; i--)
			{
				this->body[i][0].draw(' ');
				this->body[i][1].draw(' ');
				this->body[i][0].move(direction);
				this->body[i][1].move(direction);
				setTextColor(color);
				this->body[i][0].draw(figure);
				this->body[i][1].draw(figure);
			}
		}
	}
}
                         

void Ship::draw() {
	if (this->shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			setTextColor(color);
			this->body[0][i].draw(figure);
			setTextColor(Color::WHITE);
		}

	}
	else {
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				setTextColor(color);
				this->body[i][j].draw(figure);
				setTextColor(Color::WHITE);
			}
		}
	}
}

void Ship::erase() {
	if (this->shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			this->body[0][i].draw(' ');
		}
	}
	else {
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				this->body[i][j].draw(' ');
			}
		}
	}
}

Ship::~Ship() {
	for (int i = 0; i < (int)shipSize; i++) {
		delete this->body[i];
	}
	delete this->body;
}

Point Ship::getCurrentShipPoint() {
	return Point(this->body[0][0]);
}

Point* Ship::getCurrentBodyPoints() {
	Point* curPoints;
	if (this->shipSize == ShipSize::Small) {
		curPoints = new Point[2];
		for (int i = 0; i < 2; i++) {
			curPoints[i] = this->body[0][i];
		}
		
	}
	else {
		curPoints = new Point[4];
		for (int i = 0; i < 2; i++)
			for (int y = 0; y < 2; y++)
			{
				curPoints[i * 2 + y] = this->body[i][y];
			}
	}
	return curPoints;
	}
	