#include "board.h"

std::string static staticBoard = "11111111111111111111111111111111111111111111111111111111111111111111111111111111"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000022000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000022200000000000000000000000001"
"10000000000000000000000011000000000000000000000000022200000000000000000000000000"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"11111111111100000000000011000000000000000000000000011000000000000000000000000001"
"11111111111100000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"11111111111111111111111111111111111111111111111111111111111111111111111111111001";


Board::Board(): bigShip(Ship(ShipSize::Big, '@', Color::LIGHTCYAN, Point(34, 3))), smallShip(Ship(ShipSize::Small, '&', Color::LIGHTMAGENTA, Point(5, 5))) {
	for (int x = 0; x < Bounderies::rows; x++) {
		for (int y = 0; y < Bounderies::cols; y++) {
			boardGame[x][y] = staticBoard[x * Bounderies::cols + y];
		}
	}
}

void Board::setValueByIndex(Point p, BoardCellType boardCellType) {
	this->boardGame[p.getYPoint()][p.getXPoint()] = (char)boardCellType;
}

BoardCellType Board::getValueByIndex(Point p) {
	return (BoardCellType)this->boardGame[p.getXPoint()][p.getYPoint()];
}
void Board::printBoard() {
	for (int x = 0; x < Bounderies::rows; x++) {
		for (int y = 0; y < Bounderies::cols; y++) {
			BoardCellType currentCellType = this->getValueByIndex(Point(x, y));
			Point currentPoint = Point(y, x);
			if (currentCellType == BoardCellType::Wall) {
				currentPoint.draw('#');
			}
			else if (currentCellType == BoardCellType::Block) {
				currentPoint.draw('~');
			}
			else{
				currentPoint.draw(' ');
			}
		}
	}
}

void Board::start() {
	bool isHittedOnce = false;
	char key = 0;
	bool isSmallShipMove = false;
	this->printBoard();
	this->bigShip.draw();
	this->smallShip.draw();
	Point* curPoints;

	while (key != ESC){
		if (_kbhit()){
			isHittedOnce = true;
			key = _getch();
			if (getKeyByChar(key) == Keys::SwitchSmall) {
				isSmallShipMove = true;
			}
			else if (getKeyByChar(key) == Keys::SwitchBig) {
				isSmallShipMove = false;
			}
			else {
				Direction nextDirection = getDirectionByKey(key);
				if (isSmallShipMove) {
					this->smallShip.setDirection(nextDirection);
					
					if (this->isValidMove(ShipSize::Small)) {
						curPoints = this->smallShip.getCurrentBodyPoints();
						this->updateValueByPoints(curPoints, 2, BoardCellType::Empty);
						this->smallShip.move();
						curPoints = this->smallShip.getCurrentBodyPoints();
						this->updateValueByPoints(curPoints, 2, BoardCellType::SmallShip);
					}
					
				}
				else {
					this->bigShip.setDirection(nextDirection);

					if(this->isValidMove(ShipSize::Big)){
						curPoints = this->bigShip.getCurrentBodyPoints();
						this->updateValueByPoints(curPoints, 4, BoardCellType::Empty);
						this->bigShip.move();
						curPoints = this->bigShip.getCurrentBodyPoints();
						this->updateValueByPoints(curPoints, 4, BoardCellType::BigShip);
					}
				}
			}
		} else if (isHittedOnce) {
			if (isSmallShipMove) {
				if (this->isValidMove(ShipSize::Small)) {
					curPoints = this->smallShip.getCurrentBodyPoints();
					this->updateValueByPoints(curPoints, 2, BoardCellType::Empty);
					this->smallShip.move();
					curPoints = this->smallShip.getCurrentBodyPoints();
					this->updateValueByPoints(curPoints, 2, BoardCellType::SmallShip);
				}
			} else {
				if (this->isValidMove(ShipSize::Big)) {
					curPoints = this->bigShip.getCurrentBodyPoints();
					this->updateValueByPoints(curPoints, 4, BoardCellType::Empty);
					this->bigShip.move();
					curPoints = this->bigShip.getCurrentBodyPoints();
					this->updateValueByPoints(curPoints, 4, BoardCellType::BigShip);
				}
			}
		}
		Sleep(500);
	}

	setTextColor(Color::WHITE);
	clear_screen();
}

void Board::updateValueByPoints(Point* points, int size, BoardCellType cellType) {
	for (int i = 0; i < size; i++) {
		this->setValueByIndex(points[i], cellType);
	}
}

bool Board::isValidMove(ShipSize shipSize) {
	if (shipSize == ShipSize::Small) {
		return this->isSmallShipValidMove();
	}
	else {
		return this->isBigShipValidMove();
	}
}


bool Board::isSmallShipValidMove() {
	Point curShipPoint = this->smallShip.getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();

		Direction dir = this->smallShip.getDirection();

		switch ((int)dir) {
		case 0: // UP
			if ((this->getValueByIndex(Point(curShipPointY - 1, curShipPointX)) == BoardCellType::Empty
				&& this->getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1)) == BoardCellType::Empty)) {
				return true;
			}
			
			break;
		case 1: // DOWN
			if ((this->getValueByIndex(Point(curShipPointY + 1, curShipPointX)) == BoardCellType::Empty
				&& this->getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1)) == BoardCellType::Empty)) {
				return true;
			}
			
			break;
		case 2: // LEFT
			if (this->getValueByIndex(Point(curShipPointY, curShipPointX - 1)) == BoardCellType::Empty) {
				return true;
			}
			
			break;
		case 3: // RIGHT
			if (this->getValueByIndex(Point(curShipPointY, curShipPointX + 2)) == BoardCellType::Empty) {
				return true;
			}
			
			break;
		}
		return false;
}

bool Board::isBigShipValidMove() {
	Point curShipPoint = this->bigShip.getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();

	Direction dir = this->bigShip.getDirection();
	
	switch ((int)dir) {
	case 0: // UP
		if ((this->getValueByIndex(Point(curShipPointY - 1, curShipPointX)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1)) == BoardCellType::Empty)) {
			return true;
		}
		
		break;
	case 1: // DOWN
		if ((this->getValueByIndex(Point(curShipPointY + 2, curShipPointX)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curShipPointY + 2, curShipPointX + 1)) == BoardCellType::Empty)) {
			return true;
		}
			
		break;
	case 2: // LEFT
		if ((this->getValueByIndex(Point(curShipPointY, curShipPointX - 1)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curShipPointY + 1, curShipPointX - 1)) == BoardCellType::Empty)) {
			return true;
		}
			
		break;
	case 3: // RIGHT
		if ((this->getValueByIndex(Point(curShipPointY, curShipPointX + 2)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curShipPointY + 1, curShipPointX + 2)) == BoardCellType::Empty)) {
			return true;
		}
		
		break;
	}
	return false;
}