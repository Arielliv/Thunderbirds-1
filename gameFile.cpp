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
		this->file.open(fileName, std::ios::out | std::ios::in | std::ios::trunc);
		//if (isWriteMode) {
		//	this->file.open(fileName, std::ios::out);
		//}
		//else {
		//	this->file.open(fileName, std::ios::in);
		//}
		
		if (this->file.is_open()) {
			isFileOpen = true;
		}
	}
	ss.clear();
	return isFileOpen;
};

void GameFile::writeToStepsFile(int step, Point wonderGhostPoint, Direction smallShipDirection, Direction bigShipDirection) {
	std::stringstream ss;
	ss << "step: " << step << " wonderGhostPoint: x: " << wonderGhostPoint.getXPoint() << " y: " << wonderGhostPoint.getYPoint();
	if (smallShipDirection != Direction::None) {
		ss << " smallShipDirection: " << (char)smallShipDirection;
	}
	if (bigShipDirection != Direction::None) {
		ss << " bigShipDirection: " << (char)bigShipDirection;
	}
	ss << std::endl;
	this->file << ss.str();
}

void GameFile::writeToResultFile(int step, bool isLostLives, bool isFinshedScreen) {
	std::stringstream ss;
	ss << "step: " << step;
	if (isLostLives){
		ss << " isLostLives: " << isLostLives;
	}
	if (isFinshedScreen) {
		ss << " isFinshedScreen: " << isFinshedScreen;
	}
	ss << std::endl;
	this->file << ss.str();
}

void GameFile::readStepsFile(int& step, Point& wonderGhostPoint, char smallShipDirection, char bigShipDirection) {
	int wonderGhostPointX, wonderGhostPointY;
	string buf;
	std::stringstream ss;

	ss << this->file.rdbuf();
	if (ss >> buf >> step >> buf >> buf >> wonderGhostPointX >> buf >> wonderGhostPointY >> buf >> smallShipDirection >> buf >> bigShipDirection) {
		wonderGhostPoint = Point(wonderGhostPointX, wonderGhostPointY);
	}
	else {
		throw("end of file..");
	}
}

void GameFile::readResultFile(int& step, bool& isLostLives, bool& isFinshedScreen) {
	string buf;
	std::stringstream ss;

	ss << this->file.rdbuf();
	if (!(ss >> buf >> step >> buf >> isLostLives >> buf >> isFinshedScreen)) {
		throw("end of file..");
	}
}

void GameFile::closeFile() {
	this->file.close();
}