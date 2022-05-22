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
	std::ifstream file;
	bool isStepsFile;
public:
	GameFile(bool isStepsFile) : isStepsFile(isStepsFile) {};
	bool openFile(std::string fileName, int fileNumber, int screenNumber);
	void readFile();
	void writeToStepsFile(int step, Direction smallShipDirection, Direction bigShipDirection, Point wonderGhostPoint);
	void writeToResultFile();
	void closeFile();
};