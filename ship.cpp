#include "ship.h"

Ship::Ship() {
	this->isEmpty = true;
};

Ship& Ship::operator=(const Ship& s) {
	this->isEmpty = false;
	this->shipSize = s.shipSize;
	this->startPoint = s.startPoint;
	this->figure = s.figure;
	this->color = s.color;
	this->direction = s.direction;
	this->isWithColors = s.isWithColors;
	for (int i = 0; i < s.body.size();i++) {
		body[i] = s.body[i];
	}
	return *this;
}

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint, bool isWithColors) : shipSize(shipSize), figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	this->isEmpty = false;
	if (shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++) {
			this->body.push_back(Point(this->startPoint.getXPoint() + i, this->startPoint.getYPoint()));
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->body.push_back(Point(this->startPoint.getXPoint() + j, this->startPoint.getYPoint() + i));
			}
		}
	}
}

void Ship::setDirection(const Direction direction) {
	this->direction = direction;
}

Direction Ship::getDirection() const{
	return this->direction;
}

void Ship::move(vector<vector<char>>& boardGame) {
		updateValueByPoints(this->body, (int)this->shipSize, BoardCellType::Empty, boardGame);
	
		for (std::size_t i = 0; i < this->body.size(); i++) {
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}

		for (std::size_t i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}

		updateValueByPoints(this->body, (int)this->shipSize, this->shipSize == ShipSize::Small?  BoardCellType::SmallShip : BoardCellType::BigShip, boardGame);
}
                         

void Ship::draw(vector<vector<char>>& boardGame) const{
		for (std::size_t i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
		updateValueByPoints(this->body,(int)this->shipSize, this->shipSize == ShipSize::Small ? BoardCellType::SmallShip : BoardCellType::BigShip, boardGame);
}

void Ship::erase(vector<vector<char>>& boardGame) const {
	for (std::size_t i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(' ');
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	}

	updateValueByPoints(this->body, (int)this->shipSize, BoardCellType::Empty, boardGame);
}

Ship::~Ship() {
	this->body.clear();
}

Point Ship::getCurrentShipPoint() const{
	return Point(this->body[0]);
}

const vector<Point> Ship::getCurrentBodyPoints() const {
	return this->body;
}

bool Ship::isNextMoveEQCellType(const BoardCellType cellType, const vector<vector<char>>& boardGame) const {
	if (this->shipSize == ShipSize::Big) {
		return this->isBigShipNextMoveEQCellType(cellType, boardGame);
	}
	else {
		return this->isSmallShipNextMoveEQCellType(cellType, boardGame);
	}
}

bool Ship::isSmallShipNextMoveEQCellType(const BoardCellType cellType, const vector<vector<char>>& boardGame) const {
	Point curShipPoint = this->getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();

	Direction dir = this->direction;

	switch ((int)dir) {
	case 0: // UP
		if ((getValueByIndex(Point(curShipPointY - 1, curShipPointX),boardGame) == cellType
			&& getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame) == cellType)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((getValueByIndex(Point(curShipPointY + 1, curShipPointX), boardGame) == cellType
			&& getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1), boardGame) == cellType)) {
			return true;
		}

		break;
	case 2: // LEFT
		if (getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame) == cellType) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame) == cellType) {
			return true;
		}

		break;
	}
	return false;
}

bool Ship::isBigShipNextMoveEQCellType(const BoardCellType cellType, const vector<vector<char>>& boardGame) const {
	Point curShipPoint = this->getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();

	Direction dir = this->direction;

	switch ((int)dir) {
	case 0: // UP
		if ((getValueByIndex(Point(curShipPointY - 1, curShipPointX), boardGame) == cellType
			&& getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame) == cellType)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((getValueByIndex(Point(curShipPointY + 2, curShipPointX), boardGame) == cellType
			&& getValueByIndex(Point(curShipPointY + 2, curShipPointX + 1), boardGame) == cellType)) {
			return true;
		}

		break;
	case 2: // LEFT
		if (getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame) == cellType
			&& getValueByIndex(Point(curShipPointY + 1, curShipPointX - 1), boardGame) == cellType) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame) == cellType
			&& getValueByIndex(Point(curShipPointY + 1, curShipPointX + 2), boardGame) == cellType) {
			return true;
		}

		break;
	}
	return false;
}

bool Ship::isShipValidBlockMove(BoardCellType* blockType, const vector<vector<char>>& boardGame) const {
	if (this->shipSize == ShipSize::Big) {
		return this->isBigShipValidBlockMove(blockType, boardGame);
	}
	else {
		return this->isSmallShipValidMoveBlock(boardGame);
	}
}

bool Ship::isBigShipValidBlockMove(BoardCellType* blockType, const vector<vector<char>>& boardGame) const {
	Point curShipPoint = this->getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->getDirection();

	BoardCellType curCellType1, curCellType2;
	switch ((int)dir) {
	case 0: // UP
		curCellType1 = getValueByIndex(Point(curShipPointY - 1, curShipPointX),boardGame);
		curCellType2 = getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame);

		if ((curCellType1 >= BoardCellType::SmallBlock || curCellType2 >= BoardCellType::SmallBlock)
			&& (curCellType1 != BoardCellType::Wall && curCellType2 != BoardCellType::Wall)) {
			if (curCellType1 > curCellType2) {
				*blockType = curCellType1;
			}
			else {
				*blockType = curCellType2;
			}
			return true;
		}

		break;
	case 1: // DOWN
		curCellType1 = getValueByIndex(Point(curShipPointY + 2, curShipPointX), boardGame);
		curCellType2 = getValueByIndex(Point(curShipPointY + 2, curShipPointX + 1), boardGame);

		if ((curCellType1 >= BoardCellType::SmallBlock || curCellType2 >= BoardCellType::SmallBlock)
			&& (curCellType1 != BoardCellType::Wall && curCellType2 != BoardCellType::Wall)) {
			if (curCellType1 > curCellType2) {
				*blockType = curCellType1;
			}
			else {
				*blockType = curCellType2;
			}
			return true;
		}

		break;
	case 2: // LEFT
		curCellType1 = getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame);
		curCellType2 = getValueByIndex(Point(curShipPointY + 1, curShipPointX - 1), boardGame);

		if ((curCellType1 >= BoardCellType::SmallBlock || curCellType2 >= BoardCellType::SmallBlock)
			&& (curCellType1 != BoardCellType::Wall && curCellType2 != BoardCellType::Wall)) {
			if (curCellType1 > curCellType2) {
				*blockType = curCellType1;
			}
			else {
				*blockType = curCellType2;
			}
			return true;
		}

		break;
	case 3: // RIGHT
		curCellType1 = getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame);
		curCellType2 = getValueByIndex(Point(curShipPointY + 1, curShipPointX + 2), boardGame);

		if ((curCellType1 >= BoardCellType::SmallBlock || curCellType2 >= BoardCellType::SmallBlock)
			&& (curCellType1 != BoardCellType::Wall && curCellType2 != BoardCellType::Wall)) {
			if (curCellType1 > curCellType2) {
				*blockType = curCellType1;
			}
			else {
				*blockType = curCellType2;
			}
			return true;
		}

		break;
	}
	return false;
}

bool Ship::isSmallShipValidMoveBlock(const vector<vector<char>>& boardGame) const {
	Point curShipPoint = this->getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->getDirection();

	switch ((int)dir) {
	case 0: // UP
		if ((getValueByIndex(Point(curShipPointY - 1, curShipPointX), boardGame) == BoardCellType::SmallBlock
			|| getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame) == BoardCellType::SmallBlock)
			&& (getValueByIndex(Point(curShipPointY - 1, curShipPointX), boardGame) != BoardCellType::Wall
				&& getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame) != BoardCellType::Wall)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((getValueByIndex(Point(curShipPointY + 1, curShipPointX), boardGame) == BoardCellType::SmallBlock
			|| getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1), boardGame) == BoardCellType::SmallBlock)
			&& (getValueByIndex(Point(curShipPointY + 1, curShipPointX), boardGame) != BoardCellType::Wall
				&& getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1), boardGame) != BoardCellType::Wall)) {
			return true;
		}

		break;
	case 2: // LEFT
		if (getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame) == BoardCellType::SmallBlock) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame) == BoardCellType::SmallBlock) {
			return true;
		}

		break;
	}
	return false;
}

bool Ship::isShipEmpty() {
	return this->isEmpty;
}