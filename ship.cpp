#include "ship.h"

Ship& Ship::operator=(const Ship& s) {
	this->shipSize = s.shipSize;
	this->startPoint = s.startPoint;
	this->figure = s.figure;
	this->color = s.color;
	this->direction = s.direction;
	this->isWithColors = s.isWithColors;
	for (Point p : s.body) {
		body.push_back(p);
	}
	return *this;
}

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint, bool isWithColors) : shipSize(shipSize), figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	if (shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++) {
			this->body.push_back(Point(this->startPoint.getXPoint() + i, this->startPoint.getYPoint()));
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->body.push_back(Point(this->startPoint.getXPoint() + j, this->startPoint.getYPoint() + i));
			}
		}
	}
}

void Ship::setDirection(const Direction direction) {
	this->direction = direction;
}

Direction Ship::getDirection() const{
	return this->direction;
}

void Ship::move() {
		for (std::size_t i = 0; i < this->body.size(); i++) {
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}

		for (std::size_t i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}
}
                         

void Ship::draw() const{
		for (std::size_t i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
}

void Ship::erase() const {
	for (std::size_t i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(' ');
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	}
}

Ship::~Ship() {

}

Point Ship::getCurrentShipPoint() const{
	return Point(this->body[0]);
}

const vector<Point> Ship::getCurrentBodyPoints() const {
	return this->body;
}