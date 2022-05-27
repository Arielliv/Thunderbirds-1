#include "ship.h"

Ship& Ship::operator=(const Ship& s) {
	BoardGameTool::operator=(s);
	this->shipSize = s.shipSize;
	this->direction = s.direction;
	return *this;
}

Ship::Ship(ShipSize shipSize, char figure, Color color, Point startPoint, bool isWithColors) : BoardGameTool(figure, color, startPoint, isWithColors), shipSize(shipSize){
	if (shipSize == ShipSize::Small) {
		for (int i = 0; i < 2; i++) {
			this->pushToBody(Point(this->getStartPoint().getYPoint() +i, this->getStartPoint().getXPoint()));
		}
	}
	else {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->pushToBody(Point( this->getStartPoint().getYPoint() + j, this->getStartPoint().getXPoint() + i));
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

void Ship::erase(vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getIsWithColors()) {
			setTextColor(this->getColor());
		}
		this->getBody()[i].draw(' ');
		if (this->getIsWithColors()) {
			setTextColor(Color::WHITE);
		}
	}

	updateValueByPoints(this->getBody(), (int)this->shipSize, (char)BoardCellType::Empty, boardGame);
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
	Point curShipPoint = this->getCurrentPoint();
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
	Point curShipPoint = this->getCurrentPoint();
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
	Point curShipPoint = this->getCurrentPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->getDirection();
	
	char curCellType1, curCellType2;
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].getSize() <= (int)MaxSizeOfBlockToMove::Big) {
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
	Point curShipPoint = this->getCurrentPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->getDirection();
	char curCellType1, curCellType2;

	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].getSize() <=(int)MaxSizeOfBlockToMove::Small) {
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

bool Ship::shouldBlockExplodeShip(const vector<vector<char>>& boardGame, const Block& block) const {
	if ((int)this->shipSize < (int)block.getSize()) {
		vector<Point> blockBody = block.getCurrentBodyPoints();
		for (int i = 0; i < (int)block.getSize(); i++) {
			Point curBlockPoint = blockBody[i];
			int curBlockPointY = curBlockPoint.getYPoint();
			int curBlockPointX = curBlockPoint.getXPoint();

			if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) == this->getFigure()) {
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
