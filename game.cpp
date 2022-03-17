#include "game.h"

void Game::start() {
	char key = 0;
	bool isSmallShipMove = false;

	do {
		//bigShip.draw();
		if (_kbhit()){
			key = _getch();
			if (getKeyByChar(key) == Keys::SwitchSmall) {
				isSmallShipMove = true;
			}
			else if (getKeyByChar(key) == Keys::SwitchBig) {
				isSmallShipMove = false;
			}
			else {
				Direction nextDirection = getDirectionByKey(key);
				if (isSmallShipMove) {
					smallShip.setDirection(nextDirection);
					smallShip.move();
				}
				else {
					bigShip.setDirection(nextDirection);
					bigShip.move();
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