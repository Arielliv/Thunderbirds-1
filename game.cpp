#include "game.h"

void Game::start() {
	char key = 0;
	bool isSmallShipMove = false;

	do {
		if (_kbhit())
		{
			key = _getch();
			if ((Keys)key == Keys::SwitchSmall) {
				isSmallShipMove = true;
			}
			else if ((Keys)key == Keys::SwitchBig) {
				isSmallShipMove = false;
			}
			else {
				Direction nextDirection = getDirectionByKey(key);
				if (isSmallShipMove) {
					smallShip.move(nextDirection);
				}
				else {
					bigShip.move(nextDirection);
				}
			}
		}
		if (isSmallShipMove) {
			smallShip.move();
		}
		else {
			bigShip.move();
		}
		Sleep(500);
	} while (key != ESC);

	setTextColor(Color::WHITE);
	clear_screen();
}