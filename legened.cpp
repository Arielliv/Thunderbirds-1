#include "legened.h"

Legened::Legened(int location, bool isWithColors):location(location), isWithColors(isWithColors) {}

Legened& Legened::operator=(const Legened& b) {
	this->isWithColors = b.isWithColors;
	this->location = b.location;
	return *this;
}

void clearLine(const int lineNumber) {
	gotoxy(0, lineNumber);
	for (int i = 0; i < Bounderies::cols; i++) {
		std::cout << ' ';
	}
}

void Legened::printStatus(const int lives,const int time, bool isSmallShipMove) const {
	clearLine(this->location);

	if (this->isWithColors) {
		setTextColor(Color::YELLOW);
	}

	this->printTimer(time);
	this->printShipTurn(isSmallShipMove);
	this->printRemainingLives(lives);

}
void Legened::printTimer(const int time) const {
	gotoxy(8, this->location);
	std::cout << "| " << "Time left: " << time << std::endl;
}

void Legened::printShipTurn(const bool isSmallShipMove) const {
	gotoxy(28, this->location);
	string activeShip = isSmallShipMove ? "Small" : "Big";
	std::cout << "| " << "Active ship: " << activeShip << std::endl;
}

void Legened::printRemainingLives(const int lives) const {
	gotoxy(50, this->location);
	std::cout << "| " << "Remaining lives: " << lives << std::endl;
}

void Legened::printEscOptions() const {
	clearLine(this->location);
	gotoxy(13, this->location);
	if (this->isWithColors) {
		setTextColor(Color::LIGHTRED);
	}
	std::string const escOptions = "--- To exit press 9, to unpause press ESC ---";
	std::cout << escOptions << std::endl;
}