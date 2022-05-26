#include "gameFile.h"

GameFile& GameFile::operator=(const GameFile& b) {
	//should copy also file ?????????????
	this->isStepsFile = b.isStepsFile;
	return *this;
}

bool GameFile::openFile(std::string screenNumber, bool isWriteMode) {
	bool isFileOpen = false;
	std::string fileName = "";
	std::stringstream ss;

	if (this->isStepsFile) {
		ss << "tb" << screenNumber << ".steps";
	}
	else {
		ss << "tb" << screenNumber << ".result";
	}

	fileName = ss.str();

	if (fileName.size() > 0) {
		if (isWriteMode) {
			this->file.open(fileName, std::ios::out | std::ios::trunc);
		}
		else {
			this->file.open(fileName, std::ios::in);
		}
		
		if (this->file.is_open()) {
			isFileOpen = true;
		}
	}
	ss.clear();
	return isFileOpen;
};

void GameFile::writeToStepsFile(int step, Direction wonderGhostDirection, Direction smallShipDirection, Direction bigShipDirection) {
	std::stringstream ss;
	ss << "s " << step;
	if (wonderGhostDirection != Direction::None) {
		ss << " w " << (int)wonderGhostDirection;
	}
	if (smallShipDirection != Direction::None) {
		ss << " s " << (int)smallShipDirection;
	}
	if (bigShipDirection != Direction::None) {
		ss << " b " << (int)bigShipDirection;
	}
	ss << std::endl;
	this->file << ss.str();
}

void GameFile::writeToResultFile(int step, bool isLostLives, bool isFinshedScreen) {
	std::stringstream ss;
	ss << "s " << step;
	if (isLostLives){
		ss << " l " << isLostLives;
	}
	if (isFinshedScreen) {
		ss << " f " << isFinshedScreen;
	}
	ss << std::endl;
	this->file << ss.str();
}

void GameFile::readStepsFile(int& step, Direction& wonderGhostDirection, Direction& smallShipDirection, Direction& bigShipDirection) {
	std::string line;
	std::stringstream ss;
	int j = 0;

	std::getline(this->file, line);

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == 's') {
			j = 2;
			while (line[i+j] != ' ' && (i + j) < line.length()) {
				ss << line[i + j];
				j++;
			}
			ss >> step;
			i += j;
		}
		else if (line[i] == 'w') {
			i += 2;
			wonderGhostDirection = (Direction)(line[i] - '0');
		}
		else if (line[i] == 'b') {
			i += 2;
			bigShipDirection = (Direction)(line[i] - '0');
		}
		else if (line[i] == 'm') {
			i += 2;
			smallShipDirection = (Direction)(line[i] - '0');
		}
	}
}

void GameFile::readResultFile(int& step, bool& isLostLives, bool& isFinshedScreen) {
	std::string line;
	std::stringstream ss;
	int j = 0;

	std::getline(this->file, line);

	for (int i = 0; i < line.length(); i++) {
		if (line[i] == 's') {
			j = 1;
			while (line[i + j] != ' ' && (i + j) < line.length()) {
				ss << line[i + j];
				j++;
			}
			ss >> step;
		}
		else if (line[i] == 'l') {
			isLostLives = line[i + 2];
		}
		else if (line[i] == 'f') {
			isFinshedScreen = line[i + 2];
		}
	}
}

void GameFile::closeFile() {
	this->file.close();
}