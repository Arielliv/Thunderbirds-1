#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "constants.h"
#include <sstream>
#include "point.h"

class GameFile
{
private:
	std::fstream file;
	bool isStepsFile;
public:
	GameFile() {};
	GameFile(bool isStepsFile) : isStepsFile(isStepsFile) {};
	bool openFile(std::string screenNumber, bool isWriteMode);
	void readStepsFile(int& step, Direction& wonderGhostDirection, Direction& smallShipDirection, Direction& bigShipDirection, bool& isNeedSmallToChange, bool& isNeedBigToChange, bool& isNeedWonderToChange);
	void readResultFile(int& step, bool& isLostLives, bool& isFinshedScreen);
	void writeToStepsFile(int step, Direction wonderGhostDirection, Direction smallShipDirection, Direction bigShipDirection);
	void writeToResultFile(int step, bool isLostLives, bool isFinshedScreen);
	void closeFile();
	GameFile& operator=(const GameFile& b);
};