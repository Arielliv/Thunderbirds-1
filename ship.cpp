#include "ship.h"

Ship& Ship::operator=(const Ship& s) {
	this->body.reserve((int)s.shipSize);
	this->isEmpty = s.isEmpty;
	this->shipSize = s.shipSize;
	this->startPoint = s.startPoint;
	this->figure = s.figure;
	this->color = s.color;
	this->direction = s.direction;
	this->isWithColors = s.isWithColors;
	this->body = s.body;
	return *this;
}

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint, bool isWithColors) : shipSize(shipSize), figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	this->isEmpty = false;
	if (shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++) {
			this->body.push_back(Point(this->startPoint.getYPoint() +i, this->startPoint.getXPoint()));
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->body.push_back(Point( this->startPoint.getYPoint() + j, this->startPoint.getXPoint() + i));
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
		updateValueByPoints(this->body, (int)this->shipSize, (char)BoardCellType::Empty, boardGame);
	
		for (int i = 0; i < this->body.size(); i++) {
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}

		for (int i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}

		updateValueByPoints(this->body, (int)this->shipSize, this->shipSize == ShipSize::Small? (char)BoardCellType::SmallShip : (char)BoardCellType::BigShip, boardGame);
}
                         

void Ship::draw( vector<vector<char>>& boardGame) const{
		for (int i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
		updateValueByPoints(this->body,(int)this->shipSize, this->shipSize == ShipSize::Small ? (char)BoardCellType::SmallShip : (char)BoardCellType::BigShip, boardGame);
}

void Ship::erase(vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(' ');
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	}

	updateValueByPoints(this->body, (int)this->shipSize, (char)BoardCellType::Empty, boardGame);
}

Ship::~Ship() {
	this->body.clear();
}

const Point& Ship::getCurrentShipPoint() const{
	return this->body[0];
}

const vector<Point>& Ship::getCurrentBodyPoints() const {
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

	switch (dir) {
	case Direction::Up:
		if ((getValueByIndex(Point(curShipPointY - 1, curShipPointX),boardGame) == (char)cellType
			&& getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame) == (char)cellType)) {
			return true;
		}

		break;
	case Direction::Down:
		if ((getValueByIndex(Point(curShipPointY + 1, curShipPointX), boardGame) == (char)cellType
			&& getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1), boardGame) == (char)cellType)) {
			return true;
		}

		break;
	case Direction::Left:
		if (getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame) == (char)cellType) {
			return true;
		}

		break;
	case Direction::Right:
		if (getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame) == (char)cellType) {
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

	switch (dir) {
	case Direction::Up: // UP
		if ((getValueByIndex(Point(curShipPointY - 1, curShipPointX), boardGame) == (char)cellType
			&& getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame) == (char)cellType)) {
			return true;
		}

		break;
	case Direction::Down: // DOWN
		if ((getValueByIndex(Point(curShipPointY + 2, curShipPointX), boardGame) == (char)cellType
			&& getValueByIndex(Point(curShipPointY + 2, curShipPointX + 1), boardGame) == (char)cellType)) {
			return true;
		}

		break;
	case Direction::Left: // LEFT
		if (getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame) == (char)cellType
			&& getValueByIndex(Point(curShipPointY + 1, curShipPointX - 1), boardGame) == (char)cellType) {
			return true;
		}

		break;
	case Direction::Right: // RIGHT
		if (getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame) == (char)cellType
			&& getValueByIndex(Point(curShipPointY + 1, curShipPointX + 2), boardGame) == (char)cellType) {
			return true;
		}

		break;
	}
	return false;
}

bool Ship::isShipValidBlockMove(int& blockIndexToMove, const vector<vector<char>>& boardGame, vector<Block>& blocks) const {
	if (this->shipSize == ShipSize::Big) {
		return this->isBigShipValidBlockMove(blockIndexToMove, boardGame, blocks);
	}
	else {
		return this->isSmallShipValidMoveBlock(blockIndexToMove, boardGame, blocks);
	}
}

bool Ship::isBigShipValidBlockMove(int& blockIndexToMove, const vector<vector<char>>& boardGame, vector<Block>& blocks) const {
	Point curShipPoint = this->getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->getDirection();
	
	char curCellType1, curCellType2;
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].getBlockSize() <= (int)MaxSizeOfBlockToMove::Big) {
			switch (dir) {
			case Direction::Up:
				curCellType1 = getValueByIndex(Point(curShipPointY - 1, curShipPointX), boardGame);
				curCellType2 = getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame);

				if ((curCellType1 == blocks[i].getFigure() || curCellType2 == blocks[i].getFigure())
					&& (curCellType1 != (char)BoardCellType::Wall && curCellType2 != (char)BoardCellType::Wall)) {
					blockIndexToMove = i;
					return true;
				}

				break;
			case Direction::Down:
				curCellType1 = getValueByIndex(Point(curShipPointY + 2, curShipPointX), boardGame);
				curCellType2 = getValueByIndex(Point(curShipPointY + 2, curShipPointX + 1), boardGame);

				if ((curCellType1 == blocks[i].getFigure() || curCellType2 == blocks[i].getFigure())
					&& (curCellType1 != (char)BoardCellType::Wall && curCellType2 != (char)BoardCellType::Wall)) {
					blockIndexToMove = i;
					return true;
				}

				break;
			case Direction::Left:
				curCellType1 = getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame);
				curCellType2 = getValueByIndex(Point(curShipPointY + 1, curShipPointX - 1), boardGame);

				if ((curCellType1 == blocks[i].getFigure() || curCellType2 == blocks[i].getFigure())
					&& (curCellType1 != (char)BoardCellType::Wall && curCellType2 != (char)BoardCellType::Wall)) {
					blockIndexToMove = i;
					return true;
				}

				break;
			case Direction::Right:
				curCellType1 = getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame);
				curCellType2 = getValueByIndex(Point(curShipPointY + 1, curShipPointX + 2), boardGame);

				if ((curCellType1 == blocks[i].getFigure() || curCellType2 == blocks[i].getFigure())
					&& (curCellType1 != (char)BoardCellType::Wall && curCellType2 != (char)BoardCellType::Wall)) {
					blockIndexToMove = i;
					return true;
				}

				break;
			}
		}
	}
	return false;
}

bool Ship::isSmallShipValidMoveBlock(int& blockIndexToMove, const vector<vector<char>>& boardGame, vector<Block>& blocks) const {
	Point curShipPoint = this->getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->getDirection();
	char curCellType1, curCellType2;

	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].getBlockSize() <=(int)MaxSizeOfBlockToMove::Small) {
			switch (dir) {
			case Direction::Up: 
				curCellType1 = getValueByIndex(Point(curShipPointY - 1, curShipPointX), boardGame);
				curCellType2 = getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1), boardGame);

				if ((curCellType1 == blocks[i].getFigure()
					|| curCellType2 == blocks[i].getFigure())
					&& (curCellType1 != (char)BoardCellType::Wall
						&& curCellType2 != (char)BoardCellType::Wall)) {
					blockIndexToMove = i;
					return true;
				}

				break;
			case Direction::Down:
				curCellType1 = getValueByIndex(Point(curShipPointY + 1, curShipPointX), boardGame);
				curCellType2 = getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1), boardGame);

				if ((curCellType1 == blocks[i].getFigure()
					|| curCellType2 == blocks[i].getFigure())
					&& (curCellType1 != (char)BoardCellType::Wall
						&& curCellType2 != (char)BoardCellType::Wall)) {
					blockIndexToMove = i;
					return true;
				}

				break;
			case Direction::Left:
				curCellType1 = getValueByIndex(Point(curShipPointY, curShipPointX - 1), boardGame);
					
				if (curCellType1 == blocks[i].getFigure()) {
					blockIndexToMove = i;
					return true;
				}

				break;
			case Direction::Right:
				curCellType1 = getValueByIndex(Point(curShipPointY, curShipPointX + 2), boardGame);

				if (curCellType1 == blocks[i].getFigure()) {
					blockIndexToMove = i;
					return true;
				}

				break;
			}
		}
	}
	return false;
}

ShipSize Ship::getShipSize()const {
	return this->shipSize;
};

char Ship::getFigure()const {
	return this->figure;
};

bool Ship::shouldBlockExplodeShip(const vector<vector<char>>& boardGame, const Block& block) const {
	if ((int)this->shipSize < (int)block.getBlockSize()) {
		vector<Point> blockBody = block.getCurrentBodyPoints();
		for (int i = 0; i < (int)block.getBlockSize(); i++) {
			Point curBlockPoint = blockBody[i];
			int curBlockPointY = curBlockPoint.getYPoint();
			int curBlockPointX = curBlockPoint.getXPoint();

			if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) == this->figure) {
				return true;
			}
		}
	}
	return false;
}

bool Ship::isShipValidMove(const vector<vector<char>>& boardGame) const {
	return this->isNextMoveEQCellType(BoardCellType::Empty, boardGame);
}

bool Ship::isShipVictoryMove(const vector<vector<char>>& boardGame) const {
	return this->isNextMoveEQCellType(BoardCellType::Exit, boardGame);
}
