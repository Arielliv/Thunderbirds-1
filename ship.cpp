#include "ship.h"

Ship& Ship::operator=(const Ship& s) {
	this->shipSize = s.shipSize;
	this->startPoint = s.startPoint;
	this->figure = s.figure;
	this->color = s.color;
	this->direction = s.direction;
	for (int i = 0; i < (int)s.shipSize; i++) {
		body[i] = s.body[i];
	}
	return *this;
}

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint) : shipSize(shipSize), figure(figure), color(color), startPoint(startPoint) {
	if (shipSize == ShipSize::Small) {
		this->body = new Point[(int)ShipSize::Small];
		for (int i = 0; i < 2; i++) {
			this->body[i] = Point(this->startPoint.getXPoint() + i, this->startPoint.getYPoint());
		}
	}
	else {
		this->body = new Point[(int)ShipSize::Big];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->body[i * 2 + j] = Point(this->startPoint.getXPoint() + j, this->startPoint.getYPoint() + i);
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
		for (int i = 0; i < 2; i++) {
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}
		for (int i = 0; i < 2; i++) {
			setTextColor(color);
			this->body[i].draw(figure);
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}

		for (int i = 0; i < 4; i++)
		{
			setTextColor(color);
			this->body[i].draw(figure);
		}
	}
}
                         

void Ship::draw() {
	if (this->shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			setTextColor(color);
			this->body[i].draw(figure);
			setTextColor(Color::WHITE);
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			setTextColor(color);
			this->body[i].draw(figure);
			setTextColor(Color::WHITE);
		}
	}
}

void Ship::erase() {
	if (this->shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			setTextColor(color);
			this->body[i].draw(' ');
			setTextColor(Color::WHITE);
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			setTextColor(color);
			this->body[i].draw(' ');
			setTextColor(Color::WHITE);
		}
	}
}

Ship::~Ship() {
	delete this->body;
}

Point Ship::getCurrentShipPoint() {
	return Point(this->body[0]);
}

const Point* Ship::getCurrentBodyPoints() const {
	return this->body;
}
	