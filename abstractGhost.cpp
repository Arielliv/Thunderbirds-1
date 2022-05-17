#include "abstractGhost.h"

bool AbstractGhost::isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const {
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

bool AbstractGhost::isHitShip(const vector<vector<char>>& boardGame) const {
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

Direction AbstractGhost::getDirection() const {
	return this->direction;
};
GhostType AbstractGhost::getGhostType() const {
	return this->type;
};