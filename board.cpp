#include "board.h"

std::string static staticBoard = "11111111111111111111111111111111111111111111111111111111111111111111111111111111"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000000000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000000000000000000000000000000001"
"10000000000000000000000011000000000000000000000000000000000000000000000000000000"
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


Board::Board():bigShip(Ship(ShipSize::Big, '@', Color::LIGHTCYAN, Point(34, 3))), smallShip(Ship(ShipSize::Small, '&', Color::LIGHTMAGENTA, Point(5, 5))), smallBlock(Block(BlockSize::Small, '^', Color::LIGHTGREEN, Point(23,7))), bigBlock(Block(BlockSize::Big, '~', Color::RED, Point(51, 10))) {
	for (int x = 0; x < Bounderies::rows; x++) {
		for (int y = 0; y < Bounderies::cols; y++) {
			boardGame[x][y] = staticBoard[x * (int)Bounderies::cols + y];
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
			else{
				currentPoint.draw(' ');
			}
		}
	}
}

void Board::start() {
	Point* curPoints;
	BoardCellType curBoardCellType = BoardCellType::Empty;
	bool isHittedOnce = false;
	char key = 0;
	bool isSmallShipMove = false;
	this->printBoard();

	this->bigShip.draw();
	curPoints = this->bigShip.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 2, BoardCellType::BigShip);

	this->smallShip.draw();
	curPoints = this->smallShip.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 2, BoardCellType::SmallShip);

	this->bigBlock.draw();
	curPoints = this->bigBlock.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 6, BoardCellType::BigBlock);

	this->smallBlock.draw();
	curPoints = this->smallBlock.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 2, BoardCellType::SmallBlock);

	while (key != ESC && !this->isVictory){
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
					this->smallShipMove();
					BlockSize curFallingBlocks[2];
					getFallingBlockTypes(curFallingBlocks);
					dropBlocks(curFallingBlocks);
				}
				else {
					this->bigShip.setDirection(nextDirection);
					this->bigShipMove();
					BlockSize curFallingBlocks[2];
					getFallingBlockTypes(curFallingBlocks);
					dropBlocks(curFallingBlocks);
				}
			}
		} else if (isHittedOnce) {
			if (isSmallShipMove) {
				this->smallShipMove();
				BlockSize curFallingBlocks[2];
				getFallingBlockTypes(curFallingBlocks);
				dropBlocks(curFallingBlocks);
			} else {
				this->bigShipMove();
				BlockSize curFallingBlocks[2];
				getFallingBlockTypes(curFallingBlocks);
				dropBlocks(curFallingBlocks);
			}
		}
		this->updateVictory();
		Sleep(500);
	}

	setTextColor(Color::WHITE);
	clear_screen();
}

void Board::smallShipMove() {
	bool isBlockCanMove = true;
	Direction dir = this->smallShip.getDirection();
	Point* curPoints;

	if (this->isShipValidMove(ShipSize::Small) || this->isSmallShipNextToBlock()) {
		if (this->isSmallShipNextToBlock()) {
			if (this->isBlockValidMove(BlockSize::Small, dir)) {
				isBlockCanMove = true;
				this->smallBlockMove();
			}
			else {
				isBlockCanMove = false;
			}
			
		}
		if (isBlockCanMove) {
			curPoints = this->smallShip.getCurrentBodyPoints();
			this->updateValueByPoints(curPoints, 2, BoardCellType::Empty);
			this->smallShip.move();
			curPoints = this->smallShip.getCurrentBodyPoints();
			this->updateValueByPoints(curPoints, 2, BoardCellType::SmallShip);
			this->updateExitsStatus(ShipSize::Small);
		}
	}
}

void Board::bigShipMove() {
	bool isBlockCanMove = true;
	Point* curPoints;
	Direction dir = this->bigShip.getDirection();
	BoardCellType curBoardCellType = BoardCellType::Empty;

	if (this->isShipValidMove(ShipSize::Big) || this->isBigShipNextToBlock(&curBoardCellType)) {
		if (this->isBigShipNextToBlock(&curBoardCellType)) {
			if (curBoardCellType == BoardCellType::SmallBlock ) {
				if (this->isBlockValidMove(BlockSize::Small, dir)) {
					isBlockCanMove = true;
					this->smallBlockMove();
				}
				else {
					isBlockCanMove = false;
				}
				
			}
			else if (curBoardCellType == BoardCellType::BigBlock) {
				if (this->isBlockValidMove(BlockSize::Big, dir)) {
					isBlockCanMove = true;
					this->bigBlockMove();
				}
				else {
					isBlockCanMove = false;
				}
			}
		}
		if (isBlockCanMove) {
			curPoints = this->bigShip.getCurrentBodyPoints();
			this->updateValueByPoints(curPoints, 4, BoardCellType::Empty);
			this->bigShip.move();
			curPoints = this->bigShip.getCurrentBodyPoints();
			this->updateValueByPoints(curPoints, 4, BoardCellType::BigShip);
			this->updateExitsStatus(ShipSize::Big);
		}
	}
}

void Board::smallBlockMove() {
	Point* curPoints;
	curPoints = this->smallBlock.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 2, BoardCellType::Empty);
	this->smallBlock.move(this->bigShip.getDirection());
	curPoints = this->smallBlock.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 2, BoardCellType::SmallBlock);
}

void Board::bigBlockMove() {
	Point* curPoints;
	curPoints = this->bigBlock.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 6, BoardCellType::Empty);
	this->bigBlock.move(this->bigShip.getDirection());
	curPoints = this->bigBlock.getCurrentBodyPoints();
	this->updateValueByPoints(curPoints, 6, BoardCellType::BigBlock);
}

void Board::updateValueByPoints(Point* points, int size, BoardCellType cellType) {
	for (int i = 0; i < size; i++) {
		this->setValueByIndex(points[i], cellType);
	}
}

bool Board::isShipValidMove(ShipSize shipSize) {
	if (shipSize == ShipSize::Small) {
		return this->isSmallShipValidMove();
	}
	else {
		return this->isBigShipValidMove();
	}
}


bool Board::isBlockValidMove(BlockSize blockSize, Direction dir) {
	if (blockSize == BlockSize::Small) {
		return this->isSmallBlockValidMove(dir);
	}
	else {
		return this->isBigBlockValidMove(dir);
	}
}


bool Board::isSmallBlockValidMove(Direction dir) {
	Point curBlockPoint = this->smallBlock.getCurrentBlockPoint();
	int curBlockPointY = curBlockPoint.getYPoint();
	int curBlockPointX = curBlockPoint.getXPoint();

	switch ((int)dir) {
	case 0: // UP
		if ((this->getValueByIndex(Point(curBlockPointY - 1, curBlockPointX)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY - 1, curBlockPointX + 1)) == BoardCellType::Empty)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((this->getValueByIndex(Point(curBlockPointY + 1, curBlockPointX)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY + 1, curBlockPointX + 1)) == BoardCellType::Empty)) {
			return true;
		}

		break;
	case 2: // LEFT
		if (this->getValueByIndex(Point(curBlockPointY, curBlockPointX - 1)) == BoardCellType::Empty) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (this->getValueByIndex(Point(curBlockPointY, curBlockPointX + 2)) == BoardCellType::Empty) {
			return true;
		}

		break;
	}
	return false;
}

bool Board::isBigBlockValidMove(Direction dir) {
	Point curBlockPoint = this->bigBlock.getCurrentBlockPoint();
	int curBlockPointY = curBlockPoint.getYPoint();
	int curBlockPointX = curBlockPoint.getXPoint();

	switch ((int)dir) {
	case 0: // UP
		if (this->getValueByIndex(Point(curBlockPointY - 1, curBlockPointX)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY - 1, curBlockPointX + 1)) == BoardCellType::Empty) {
			return true;
		}

		break;
	case 1: // DOWN
		if (this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1)) == BoardCellType::Empty) {
			return true;
		}

		break;
	case 2: // LEFT
		if (this->getValueByIndex(Point(curBlockPointY, curBlockPointX - 1)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY + 1, curBlockPointX - 1)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY + 2, curBlockPointX - 1)) == BoardCellType::Empty) {
			return true;
		}
		
		break;
	case 3: // RIGHT
		if (this->getValueByIndex(Point(curBlockPointY, curBlockPointX + 2)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY + 1, curBlockPointX + 2)) == BoardCellType::Empty
			&& this->getValueByIndex(Point(curBlockPointY + 2, curBlockPointX + 2)) == BoardCellType::Empty){
			return true;
		}

		break;
	}
	return false;
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


bool Board::isSmallShipNextToBlock() {
	Point curShipPoint = this->smallShip.getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->smallShip.getDirection();

	switch ((int)dir) {
	case 0: // UP
		if ((this->getValueByIndex(Point(curShipPointY - 1, curShipPointX)) == BoardCellType::SmallBlock
			|| this->getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1)) == BoardCellType::SmallBlock)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((this->getValueByIndex(Point(curShipPointY + 1, curShipPointX)) == BoardCellType::SmallBlock
			|| this->getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1)) == BoardCellType::SmallBlock)) {
			return true;
		}

		break;
	case 2: // LEFT
		if (this->getValueByIndex(Point(curShipPointY, curShipPointX - 1)) == BoardCellType::SmallBlock) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (this->getValueByIndex(Point(curShipPointY, curShipPointX + 2)) == BoardCellType::SmallBlock) {
			return true;
		}

		break;
	}
	return false;
}

bool Board::isBigShipNextToBlock(BoardCellType* blockType) {
	Point curShipPoint = this->bigShip.getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();
	Direction dir = this->bigShip.getDirection();

	BoardCellType curCellType1, curCellType2;
	switch ((int)dir) {
	case 0: // UP
		 curCellType1 = this->getValueByIndex(Point(curShipPointY - 1, curShipPointX));
		 curCellType2 = this->getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1));

		if (curCellType1 >= BoardCellType::SmallBlock || curCellType2 >= BoardCellType::SmallBlock) {
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
		 curCellType1 = this->getValueByIndex(Point(curShipPointY + 2, curShipPointX));
		 curCellType2 = this->getValueByIndex(Point(curShipPointY + 2, curShipPointX + 1));

		if (curCellType1>= BoardCellType::SmallBlock|| curCellType2 >= BoardCellType::SmallBlock) {
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
		 curCellType1 = this->getValueByIndex(Point(curShipPointY, curShipPointX - 1));
		 curCellType2 = this->getValueByIndex(Point(curShipPointY + 1, curShipPointX - 1));

		if (curCellType1 >= BoardCellType::SmallBlock || curCellType2 >= BoardCellType::SmallBlock) {
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
		 curCellType1 = this->getValueByIndex(Point(curShipPointY, curShipPointX + 2));
		 curCellType2 = this->getValueByIndex(Point(curShipPointY + 1, curShipPointX + 2));

		if (curCellType1 >= BoardCellType::SmallBlock|| curCellType2 >= BoardCellType::SmallBlock) {
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

void Board::getFallingBlockTypes(BlockSize* results) {
	Point curBlockPoint;
	int curBlockPointY, curBlockPointX, counter = 0;

	curBlockPoint = this->smallBlock.getCurrentBlockPoint();
	curBlockPointY = curBlockPoint.getYPoint();
	curBlockPointX = curBlockPoint.getXPoint();

	if (this->getValueByIndex(Point(curBlockPointY + 1, curBlockPointX)) == BoardCellType::Empty
		&& this->getValueByIndex(Point(curBlockPointY + 1, curBlockPointX + 1)) == BoardCellType::Empty) {
		results[counter] = BlockSize::Small;
		counter++;
	}

	curBlockPoint = this->bigBlock.getCurrentBlockPoint();
	curBlockPointY = curBlockPoint.getYPoint();
	curBlockPointX = curBlockPoint.getXPoint();

	if (this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX)) == BoardCellType::Empty
		&& this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1)) == BoardCellType::Empty) {
		results[counter] = BlockSize::Big;
		counter++;
	}
}

void Board::dropBlocks(const BlockSize(&fallingBlocks)[2]) {
	Point* curPoints;
	for (BlockSize curBlockSize : fallingBlocks) {
		if (curBlockSize == BlockSize::Small) {
			if (this->isBlockValidMove(BlockSize::Small, Direction::Down)) {

				curPoints = this->smallBlock.getCurrentBodyPoints();
				this->updateValueByPoints(curPoints, 2, BoardCellType::Empty);
				this->smallBlock.move(Direction::Down);
				curPoints = this->smallBlock.getCurrentBodyPoints();
				this->updateValueByPoints(curPoints, 2, BoardCellType::SmallBlock);
			}
		}
		else if (curBlockSize == BlockSize::Big) {
			if (this->isBlockValidMove(BlockSize::Big, Direction::Down)) {


				curPoints = this->bigBlock.getCurrentBodyPoints();
				this->updateValueByPoints(curPoints, 6, BoardCellType::Empty);
				this->bigBlock.move(Direction::Down);
				curPoints = this->bigBlock.getCurrentBodyPoints();
				this->updateValueByPoints(curPoints, 6, BoardCellType::SmallBlock);
			}
		}
	}
}

void Board::updateExitsStatus(ShipSize shipSize) {
	Point curPoint;
	if (shipSize == ShipSize::Small) {
		curPoint = this->smallShip.getCurrentShipPoint();
		if (this->getValueByIndex(Point(curPoint.getYPoint(),curPoint.getXPoint())) == BoardCellType::SmallExit) {
			this->exitsStatus[0] = true;
		}
	}
	else {
		curPoint = this->bigShip.getCurrentShipPoint();
		if (this->getValueByIndex(Point(curPoint.getYPoint(), curPoint.getXPoint())) == BoardCellType::BigExit) {
			this->exitsStatus[1] = true;
		}
	}
}

bool Board::updateVictory() {
	bool isVictory = true;
	for (bool status : this->exitsStatus) {
		if (!status) {
			isVictory = false;
		}
	}
	return isVictory;
}
