#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "constants.h"
#include <sstream>

class GameFile {
private:
	std::ifstream inFile;
public:
	
	bool openFile(std::string fileName);
	void readFile(int& time, int& controlledShip, std::string& boardGame, int& legendLocation, int& numOfBlocks);
	void closeFile();
};

