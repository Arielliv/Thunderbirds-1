#include "board.h"
#include "point.h"

void Point::draw(char ch) {
	gotoxy(this->x, this->y);
	cout << ch << endl;
}

int Point::getXPoint() {
	return this->x;
}

int Point::getYPoint() {
	return this->y;
}

void Point::move(Direction direction) {
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