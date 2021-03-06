#include "boardFile.h"

bool BoardFile::openFile(std::string name, int fileNumber) {
	bool isFileOpen = false;
	int fileCounter = fileNumber + 1;
	std::string fileName = "";
	std::stringstream ss;

	if (name.size() > 0) {
		this->inFile.open(name, std::ios::in);
		if (this->inFile.is_open()) {
			isFileOpen = true;
		}
	}

	else {
		while (fileCounter < 4 && !isFileOpen) {
			ss << "tb0" << fileCounter << ".screen";
			fileName = ss.str();
			this->inFile.open(fileName, std::ios::in);

			fileCounter++;

			if (this->inFile.is_open()) {
				isFileOpen = true;
			}

			ss.clear();
		}

		if (fileCounter > 4) {
			return false;
		}
	}

	return isFileOpen;
}

void BoardFile::readFile(int& time, int& controlledShip, std::string& boardGame, int& legendLocation, int& numOfBlocks, int& numOfGhosts) {
	std::string boardLine;
	int i = 0;
	
	if (this->inFile.is_open()) {
		this->inFile >> time;
		this->inFile >> controlledShip;
		this->inFile >> numOfBlocks;
		this->inFile >> numOfGhosts;

		while (i < Bounderies::rows +1) {
			getline(this->inFile, boardLine);
			boardGame += boardLine;
			i++;
		}
	}

	legendLocation = i-1;
}

void BoardFile::closeFile() {
	this->inFile.close();
	this->inFile.clear();
}