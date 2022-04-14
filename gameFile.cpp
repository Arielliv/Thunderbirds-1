#include "gameFile.h"

bool GameFile::openFile(std::string name) {
	bool isFileOpen = false;
	int fileCounter = 1;
	std::string fileName = "";
	std::stringstream ss;

	if (name.size() > 0) {
		this->inFile.open(name, std::ios::in);
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

	return true;
}

void GameFile::readFile(int& lives, int& time, int& controlledShip, std::string& boardGame, int& legendLocation) {
	std::string boardLine;
	int i = 0;
	
	if (this->inFile.is_open()) {
		bool a = this->inFile.peek() == std::ifstream::traits_type::eof();
		this->inFile >> lives;
		this->inFile >> time;
		this->inFile >> controlledShip;

		while (i < Bounderies::rows) {
			getline(this->inFile, boardLine);
			boardGame += boardLine;
			i++;
		}
	}

	legendLocation = i + 3;
	//this->inFile.close();
}