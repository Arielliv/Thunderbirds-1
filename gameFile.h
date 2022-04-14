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
	void readFile(std::string& lives, std::string& time, std::string& controlledShip, std::string& boardGame, int& legendLocation);
};

