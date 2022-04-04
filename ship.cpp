#include "ship.h"

Ship& Ship::operator=(const Ship& s) {
	this->shipSize = s.shipSize;
	this->startPoint = s.startPoint;
	this->figure = s.figure;
	this->color = s.color;
	this->direction = s.direction;
	this->isWithColors = s.isWithColors;
	for (int i = 0; i < (int)s.shipSize; i++) {
		body[i] = s.body[i];
	}
	return *this;
}

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint, bool isWithColors) : shipSize(shipSize), figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	if (shipSize == ShipSize::Small) {
		this->body = new Point[(int)ShipSize::Small];
		for (int i = 0; i < 2; i++) {
			this->body[i] = Point(this->startPoint.getXPoint() + i, this->startPoint.getYPoint());
		}
	}
	else {
		this->body = new Point[(int)ShipSize::Big];
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->body[i * 2 + j] = Point(this->startPoint.getXPoint() + j, this->startPoint.getYPoint() + i);
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

void Ship::move() {
	if (this->shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++) {
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}
		for (int i = 0; i < 2; i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}

		for (int i = 0; i < 4; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}
	}
}
                         

void Ship::draw() const{
	if (this->shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
	}
}

void Ship::erase() const {
	if (this->shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(' ');
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(' ');
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
	}
}

Ship::~Ship() {
	delete this->body;
}

Point Ship::getCurrentShipPoint() const{
	return Point(this->body[0]);
}

const Point* Ship::getCurrentBodyPoints() const {
	return this->body;
}

bool Ship::isBigShipNextMoveEQCellType(const BoardCellType cellType, const char(&boardGame)[Bounderies::rows][Bounderies::cols]) const {
	Point curShipPoint = this->getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();


	switch ((int)this->direction) {
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

//void Ship::smallShipMove(Board &board) {
//	bool isBlockCanMove = true;
//
//	if ((this->isShipValidMove(ShipSize::Small) || this->isSmallShipValidMoveBlock()) && !this->exitsStatus[0]) {
//		if (this->isSmallShipValidMoveBlock()) {
//			if (this->isBlockValidMove(BlockSize::Small, this->direction)) {
//				isBlockCanMove = true;
//				this->smallBlockMove(this->direction);
//			}
//			else {
//				isBlockCanMove = false;
//			}
//		}
//		if (isBlockCanMove) {
//			this->updateValueByCellType(BoardCellType::SmallShip, true);
//			this->smallShip.move();
//			this->updateValueByCellType(BoardCellType::SmallShip, false);
//		}
//	}
//
//	if (this->isSmallShipVictoryMove()) {
//		this->updateExitsStatus(ShipSize::Small);
//		this->smallShip.erase();
//		this->updateValueByCellType(BoardCellType::SmallShip, true);
//	}
//}
	