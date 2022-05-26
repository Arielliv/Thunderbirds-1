#include "ghost.h"

Ghost& Ghost::operator=(const Ghost& b)  {
	this->type = b.type;
	this->direction = b.direction;
	return *this;
}

void Ghost::moveAuto(vector<vector<char>>& boardGame) {
	this->move(this->direction, boardGame);
}

bool Ghost::isValidMoveAuto(const vector<vector<char>>& boardGame) {
	Point curGhostPoint = this->getCurrentPoint();
	int curGhostPointY = curGhostPoint.getYPoint();
	int curGhostPointX = curGhostPoint.getXPoint();

	Direction dir = this->direction;

	switch (dir) {
	case Direction::Up:
		if (getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == (char)BoardCellType::Empty ||
			getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	case Direction::Down:
		if (getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == (char)BoardCellType::Empty ||
			getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	case Direction::Left:
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == (char)BoardCellType::Empty ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	case Direction::Right:
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == (char)BoardCellType::Empty ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	}
	return false;
}

bool Ghost::isHitShip(const vector<vector<char>>& boardGame) {
	Point curGhostPoint = this->getCurrentPoint();
	int curGhostPointY = curGhostPoint.getYPoint();
	int curGhostPointX = curGhostPoint.getXPoint();

	Direction dir = this->getDirection();

	switch (dir) {
	case Direction::Up:
		if (getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	case Direction::Down:
		if (getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	case Direction::Left:
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	case Direction::Right:
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == (char)BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == (char)BoardCellType::BigShip) {
			return true;
		}

		break;
	}
	return false;
}

Direction Ghost::getDirection() const {
	return this->direction;
};
GhostType Ghost::getGhostType() const {
	return this->type;
};

void Ghost::setDirection(const Direction direction) {
	this->direction = direction;
}

bool Ghost::shouldSaveToFile() const {
	return false;
}

GhostType Ghost::getType() const {
	return this->type;
}