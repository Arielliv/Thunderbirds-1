#include "wonderGhost.h"

WonderGhost::WonderGhost(char figure, Color color, Point startPoint, bool isWithColors, const vector<vector<char>>& boardGame) : Ghost(figure, color, startPoint, isWithColors, GhostType::Wondering) {
	this->nextPoint = this->generateNextPoint(boardGame, true);
};

WonderGhost& WonderGhost::operator=(const WonderGhost& b) {
	this->nextPoint = b.getNextPoint();
	return *this;
}

Point WonderGhost::getNextPoint() const{
	return this->nextPoint;
}

bool WonderGhost::isValidMoveAuto(const vector<vector<char>>& boardGame) const {
	return true;
}

bool WonderGhost::isHitShip(const vector<vector<char>>& boardGame) {
	this->nextPoint = this->generateNextPoint(boardGame, false);

	BoardCellType currBoardCellType = (BoardCellType)getValueByIndex(this->nextPoint, boardGame);

	if (currBoardCellType == BoardCellType::BigShip
		|| currBoardCellType == BoardCellType::SmallShip) {
		return true;
	}
	else {
		return false;
	}
}

void WonderGhost::moveAuto(vector<vector<char>>& boardGame) {
	updateValueByPoints(this->getBody(), this->getSize(), (char)BoardCellType::Empty, boardGame);
	this->getBody()[0].draw(' ');
	
	if (this->getIsWithColors()) {
		setTextColor(this->getColor());
	}

	this->setBodyAt(Point(this->nextPoint.getYPoint(), this->nextPoint.getXPoint()), 0);
	this->getBody()[0].draw(this->getFigure());
	updateValueByPoints(this->getBody(), this->getSize(), this->getFigure(), boardGame);
}

Point WonderGhost::generateNextPoint(const vector<vector<char>>& boardGame, bool isFirst) {
	bool isValidPoint = false;
	Point newPoint;
	BoardCellType currBoardCellType;
	while (!isValidPoint) {
		newPoint = Point(getRandomNum(1, Bounderies::rows - 1), getRandomNum(1, Bounderies::cols - 1));
		currBoardCellType = (BoardCellType)getValueByIndex(newPoint, boardGame);
		if (isFirst) {
			if (currBoardCellType == BoardCellType::Empty) {
				isValidPoint = true;
			}
		} else{
			if (currBoardCellType == BoardCellType::Empty
				|| currBoardCellType == BoardCellType::BigShip
				|| currBoardCellType == BoardCellType::SmallShip) {
				isValidPoint = true;
			}
		}
	}

	return newPoint;
};