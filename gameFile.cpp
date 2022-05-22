#include "gameFile.h"

bool GameFile::openFile(std::string fileName, int fileNumber, int screenNumber) {
	bool isFileOpen = false;
	std::string fileName = "";
	std::stringstream ss;

	if (fileName.size() > 0) {
		this->file.open(fileName, std::ios::in);
		if (this->file.is_open()) {
			isFileOpen = true;
		}
	}

	else {
		if (this->isStepsFile) {
			ss << "tb" << screenNumber << ".steps";
		}
		else {
			ss << "tb" << screenNumber << ".result";
		}
		fileName = ss.str();
		this->file.open(fileName, std::ios::in);

		if (this->file.is_open()) {
			isFileOpen = true;
		}
		ss.clear();
	}

	return isFileOpen;
};

void GameFile::readFile() {};

void GameFile::writeToFile() {

};
void GameFile::closeFile() {};