#pragma once

#include "constants.h"
#include "utils.h"
#include "ioUtils.h"

class Legened
{
	int location;
	bool isWithColors;
private:
	void printTimer(const int time) const;
	void printShipTurn(const bool isSmallShipMove) const;
	void printRemainingLives(const int lives) const;
	
public:
	Legened() {};
	Legened(int location, bool isWithColors);
	void printStatus(const int lives, const int time,const bool isSmallShipMove) const;
	friend void clearLine(const int lineNumber);
	void printEscOptions() const;
	Legened& operator=(const Legened& b);
	void printResultTest(bool isCorrect) const;
};

