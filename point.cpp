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
		if (y < 1) {
			y = Bounderies::rows -1;
		}
		break;
	case 1: // DOWN
		++this->y;
		if (y > Bounderies::rows - 1) {
			y = 1;
		}
		break;
	case 2: // LEFT
		--this->x;
		if (x < 1) {
			x = Bounderies::cols - 1;
		}
		break;
	case 3: // RIGHT
		++this->x;
		if (x > Bounderies::cols - 1) {
			x = 1;
		}
		break;
	}
}