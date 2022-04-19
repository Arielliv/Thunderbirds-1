#include "board.h"
#include "point.h"

void Point::draw(char ch) const{
	gotoxy(this->x, this->y);
	cout << ch << endl;
}

int Point::getXPoint() const {
	return this->x;
}

int Point::getYPoint() const {
	return this->y;
}

void Point::move(const Direction direction) {
	switch ((int)direction) {
	case 0: // UP
		--this->y;
		if (this->y < 1) {
			this->y = Bounderies::rows -1;
		}
		break;
	case 1: // DOWN
		++this->y;
		if (this->y > Bounderies::rows - 1) {
			this->y = 1;
		}
		break;
	case 2: // LEFT
		--this->x;
		if (this->x < 1) {
			this->x = Bounderies::cols - 1;
		}
		break;
	case 3: // RIGHT
		++this->x;
		if (this->x > Bounderies::cols - 1) {
			this->x = 1;
		}
		break;
	}
}

Point::~Point() {
	this->x = NULL;
	this->y = NULL;
}

bool Point::operator==(const Point& p) const {
	return this->x == p.getXPoint() && this->y == p.getYPoint();
}

Point& Point::operator=(const Point& p) {
	this->x = p.getXPoint();
	this->y = p.getYPoint();
	return *this;
}