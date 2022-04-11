#include "ghost.h"

Ghost::Ghost(char figure, Color color, Point startPoint, bool isWithColors, GhostType type, Direction direction):figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors),body(startPoint), direction(direction), type(type) {};
Ghost& Ghost::operator=(const Ghost& b) {
	this->figure = b.figure;
	this->color = b.color;
	this->startPoint = b.startPoint;
	this->isWithColors = b.isWithColors;
	this->body = b.body;
	this->type = b.type;
	this->direction = b.direction;
	return *this;
}

Point Ghost::getCurrentGhostPoint() const {
	return this->body;
}

void Ghost::move(vector<vector<char>>& boardGame) {
	updateValueByPoints({ this->body }, 1, BoardCellType::Empty, boardGame);

	this->body.draw(' ');
	this->body.move(this->direction);
	if (this->isWithColors) {
		setTextColor(color);
	}
	this->body.draw(this->figure);

	updateValueByPoints({ this->body }, 1,  BoardCellType::Ghost, boardGame);
}

void Ghost::draw(vector<vector<char>>& boardGame) const {
	
		if (this->isWithColors) {
			setTextColor(this->color);
		}
		this->body.draw(figure);
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	
		updateValueByPoints({ this->body }, 1, BoardCellType::Ghost, boardGame);
}

bool Ghost::isHitShip(const vector<vector<char>>& boardGame) const {
	Point curGhostPoint = this->getCurrentGhostPoint();
	int curGhostPointY = curGhostPoint.getYPoint();
	int curGhostPointX = curGhostPoint.getXPoint();

	Direction dir = this->direction;

	switch ((int)dir) {
	case 0: // UP
		if (getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	case 1: // DOWN
		if (getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	case 2: // LEFT
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	}
	return false;
}

bool Ghost::isValidMove(const vector<vector<char>>& boardGame) const {
	Point curGhostPoint = this->getCurrentGhostPoint();
	int curGhostPointY = curGhostPoint.getYPoint();
	int curGhostPointX = curGhostPoint.getXPoint();

	Direction dir = this->direction;

	switch ((int)dir) {
	case 0: // UP
		if (getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == BoardCellType::Empty || 
			getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY - 1, curGhostPointX), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	case 1: // DOWN
		if (getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == BoardCellType::Empty ||
			getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY + 1, curGhostPointX), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	case 2: // LEFT
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == BoardCellType::Empty ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == BoardCellType::SmallShip || 
			getValueByIndex(Point(curGhostPointY, curGhostPointX - 1), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == BoardCellType::Empty ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == BoardCellType::SmallShip ||
			getValueByIndex(Point(curGhostPointY, curGhostPointX + 2), boardGame) == BoardCellType::BigShip) {
			return true;
		}

		break;
	}
	return false;
}

void Ghost::setDirection(const Direction direction) {
	this->direction = direction;
}

Direction Ghost::getDirection() const {
	return this->direction;
}

GhostType Ghost::getGhostType() const {
	return this->type;
}