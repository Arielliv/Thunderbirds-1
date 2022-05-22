#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "constants.h"
#include <sstream>

class BoardFile {
private:
	std::ifstream inFile;
public:
	bool openFile(std::string fileName, int fileNumber);
	void readFile(int& time, int& controlledShip, std::string& boardGame, int& legendLocation, int& numOfBlocks, int& numOfGhosts);
	void closeFile();
};

