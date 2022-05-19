#include "wonderGhost.h"

bool WonderGhost::isValidMoveAuto(const vector<vector<char>>& boardGame) const {
	return true;
}

bool WonderGhost::isHitShip(const vector<vector<char>>& boardGame) const {
	BoardCellType currBoardCellType = (BoardCellType)getValueByIndex(this->getBody()[0], boardGame);

	if (currBoardCellType == BoardCellType::BigShip
		|| currBoardCellType == BoardCellType::SmallShip) {
		return true;
	}
	else {
		return false;
	}
}

void WonderGhost::moveAuto(vector<vector<char>>& boardGame) {
	this->nextPoint = this->generateNextPoint(boardGame);

	updateValueByPoints(this->getBody(), this->getSize(), (char)BoardCellType::Empty, boardGame);
	this->getBody()[0].draw(' ');
	
	if (this->getIsWithColors()) {
		setTextColor(this->getColor());
	}
    
	this->setBodyAt(this->nextPoint, 0);
	this->getBody()[0].draw(this->getFigure());
	updateValueByPoints(this->getBody(), this->getSize(), this->getFigure(), boardGame);
}

Point WonderGhost::generateNextPoint(const vector<vector<char>>& boardGame) {
	bool isValidPoint = false;
	Point newPoint;
	BoardCellType currBoardCellType;
	while (!isValidPoint) {
		newPoint = Point(getRandomNum(1, Bounderies::cols-1), getRandomNum(1, Bounderies::rows - 1));
		currBoardCellType = (BoardCellType)getValueByIndex(newPoint, boardGame);
		if (currBoardCellType == BoardCellType::Empty 
			|| currBoardCellType == BoardCellType::BigShip 
			|| currBoardCellType == BoardCellType::SmallShip) {
			isValidPoint = true;
		}
	}

	return newPoint;
};