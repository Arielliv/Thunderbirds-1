#include "board.h"
#include "point.h"

void point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}

void point::move(Direction direction) {
	switch ((int)direction) {
	case 0: // UP
		--y;
		if (y < 1) {
			y = Bounderies::right -1;
		}
		break;
	case 1: // DOWN
		++y;
		if (y > Bounderies::right - 1) {
			y = 1;
		}
		break;
	case 2: // LEFT
		--x;
		if (x < 1) {
			x = Bounderies::down - 1;
		}
		break;
	case 3: // RIGHT
		++x;
		if (x > Bounderies::down - 1) {
			x = 1;
		}
		break;
	}
}