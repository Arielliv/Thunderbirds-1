#include "board.h"

std::string const staticBoard = "11111111111111111111111111111111111111111111111111111111111111111111111111111111"	
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000000000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011111111111100000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000011100000000000000000000000001"
"10000000000000000000000011000000000000000000000000000000000000000000000000000001"
"10000000000000000000000011000000000000000000000000000000000000000000000000000001"
"10000000000000000000000011000000000000000000000000000000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011111111111111000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"11111111111100000000000011000000000000000000000000011000000000000000000000000001"
"11111111111100000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000000000000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"10000000000000000000000011000000001100000000000000011000000000000000000000000001"
"11111111111111111111111111111111111111111111111111111111111111111111111111111441";


Board& Board::operator=(const Board& b) {
	this->bigShip = b.bigShip;
	this->smallShip = b.smallShip;
	this->bigBlock = b.bigBlock;
	this->smallBlock = b.smallBlock;
	this->isVictory = b.isVictory;
	this->isSmallShipMove = b.isSmallShipMove;
	this->time = b.time;
	this->isLoss = b.isLoss;
	this->isWithColors = b.isWithColors;

	for (int i = 0; i < 2; i++) {
		this->exitsStatus[i] = b.exitsStatus[i];
	}
	for (int x = 0; x < (int)Bounderies::rows; x++) {
		for (int y = 0; y < (int)Bounderies::cols; y++) {
			boardGame[x][y] = b.boardGame[x][y];
		}
	}
	return *this;
}

Board::Board(bool isWithColors):bigShip(Ship(ShipSize::Big, '@', Color::LIGHTCYAN, Point(34, 3), isWithColors)), smallShip(Ship(ShipSize::Small, '&', Color::LIGHTMAGENTA, Point(5, 5), isWithColors)), smallBlock(Block(BlockSize::Small, '^', Color::LIGHTGREEN, Point(23,7), isWithColors)), bigBlock(Block(BlockSize::Big, '~', Color::RED, Point(51, 10), isWithColors)), isWithColors(isWithColors) {
	int cur;
	for (int x = 0; x < (int)Bounderies::rows; x++) {
		for (int y = 0; y < (int)Bounderies::cols; y++) {
			cur = x * (int)Bounderies::cols + y;
			boardGame[x][y] = staticBoard[cur];
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
void Board::initBoard() {
	this->printBoard();

	this->bigShip.draw();
	this->updateValueByCellType(BoardCellType::BigShip, false);

	this->smallShip.draw();
	this->updateValueByCellType(BoardCellType::SmallShip, false);

	this->bigBlock.draw();
	
	this->updateValueByCellType(BoardCellType::BigBlock, false);
	this->smallBlock.draw();
	this->updateValueByCellType(BoardCellType::SmallBlock, false);
}

bool Board::runTheGame(int lives) {
	bool isHittedOnce = false;
	char key = 0;
	while (key != ESC && !this->isVictory && this->time > 0 && !this->isLoss) {
		if (_kbhit()) {
			key = _getch();
			if (key != ESC) {
				isHittedOnce = true;
			}
			if (getKeyByChar(key) == Keys::SwitchSmall) {
				this->isSmallShipMove = true;
			}
			else if (getKeyByChar(key) == Keys::SwitchBig) {
				this->isSmallShipMove = false;
			}
			else {
				if (key != ESC) {
					Direction nextDirection = getDirectionByKey(key);
					if (this->isSmallShipMove) {
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
			}
		}
		else if (isHittedOnce && !this->isLoss) {
			if (this->isSmallShipMove) {
				this->smallShipMove();
				BlockSize curFallingBlocks[2];
				getFallingBlockTypes(curFallingBlocks);
				dropBlocks(curFallingBlocks);
			}
			else {
				this->bigShipMove();
				BlockSize curFallingBlocks[2];
				getFallingBlockTypes(curFallingBlocks);
				dropBlocks(curFallingBlocks);
			}
		}
		this->updateVictory();
		if (isHittedOnce) {
			this->time--;
		}
		this->printStatus(lives);
		Sleep(200);
	}
	if (key == ESC) {
		return true;
	}
	else {
		return false;
	}
}
bool Board::play(bool *isEsc,int lives) {
	bool shouldExitLoop = false;
	bool isFirstEsc = false;
	char key = 0;
	this->initBoard();
	while (key != ESC_SECOND && !shouldExitLoop) {
		isFirstEsc = this->runTheGame(lives);
		if (isFirstEsc) {
			while (key != ESC_SECOND && key != ESC) {
				if (_kbhit()) {
					key = _getch();
				}
				Sleep(200);
			}
		}
		else {
			shouldExitLoop = true;
		}
	}
	
	if (!shouldExitLoop && key == ESC_SECOND) {
		*isEsc = true;
	}

	setTextColor(Color::WHITE);
	clear_screen();
	return this->isVictory;
}

void Board::smallShipMove() {
	bool isBlockCanMove = true;
	Direction dir = this->smallShip.getDirection();

	if ((this->isShipValidMove(ShipSize::Small) || this->isSmallShipNextToBlock()) && !this->exitsStatus[0]) {
		if (this->isSmallShipNextToBlock()) {
			if (this->isBlockValidMove(BlockSize::Small, dir)) {
				isBlockCanMove = true;
				this->smallBlockMove(dir);
			}
			else {
				isBlockCanMove = false;
			}
		}
		if (isBlockCanMove) {
			this->updateValueByCellType(BoardCellType::SmallShip, true);
			this->smallShip.move();
			this->updateValueByCellType(BoardCellType::SmallShip, false);	
		}
	}

	if (this->isSmallShipVictoryMove()) {
		this->updateExitsStatus(ShipSize::Small);
		this->smallShip.erase();
		this->updateValueByCellType(BoardCellType::SmallShip, true);
	}
}

void Board::bigShipMove() {
	bool isBlockCanMove = true;
	Direction dir = this->bigShip.getDirection();
	BoardCellType curBoardCellType = BoardCellType::Empty;

	if ((this->isShipValidMove(ShipSize::Big) || this->isBigShipNextToBlock(&curBoardCellType)) && !this->exitsStatus[1]) {
		if (this->isBigShipNextToBlock(&curBoardCellType)) {
			if (curBoardCellType == BoardCellType::SmallBlock ) {
				if (this->isBlockValidMove(BlockSize::Small, dir)) {
					isBlockCanMove = true;
					this->smallBlockMove(dir);
				}
				else {
					isBlockCanMove = false;
				}
			}
			else if (curBoardCellType == BoardCellType::BigBlock) {
				if (this->isBlockValidMove(BlockSize::Big, dir)) {
					isBlockCanMove = true;
					this->bigBlockMove(dir);
				}
				else {
					isBlockCanMove = false;
				}
			}
		}
		if (isBlockCanMove) {
			this->updateValueByCellType(BoardCellType::BigShip, true);
			this->bigShip.move();
			this->updateValueByCellType(BoardCellType::BigShip, false);
		}
	}

	if (this->isBigShipVictoryMove()) {
		this->updateExitsStatus(ShipSize::Big);
		this->bigShip.erase();
		this->updateValueByCellType(BoardCellType::BigShip, true);
	}
}

void Board::smallBlockMove(Direction dir) {
	this->updateValueByCellType(BoardCellType::SmallBlock, true);
	this->smallBlock.move(dir);
	this->updateValueByCellType(BoardCellType::SmallBlock, false);
}

void Board::bigBlockMove(Direction dir) {
	this->updateValueByCellType(BoardCellType::BigBlock, true);
	this->bigBlock.move(dir);
	this->updateValueByCellType(BoardCellType::BigBlock, false);
}
void Board::updateValueByCellType(BoardCellType cellType, bool shouldErase) {
	/*
	SmallShip = '2',
	BigShip = '3',
	SmallBlock = '5',
	BigBlock = '6',
	*/
	const Point* curPoints;
	
	switch ((char)cellType) {
	case '2': // SmallShip
		curPoints = this->smallShip.getCurrentBodyPoints();
		if (shouldErase) {
			this->updateValueByPoints(curPoints, 2, BoardCellType::Empty);
		}
		else {
			this->updateValueByPoints(curPoints, 2, BoardCellType::SmallShip);
		}
		break;
	case '3': // BigShip
		curPoints = this->bigShip.getCurrentBodyPoints();
		if (shouldErase) {
			this->updateValueByPoints(curPoints, 4, BoardCellType::Empty);
		}
		else {
			this->updateValueByPoints(curPoints, 4, BoardCellType::BigShip);
		}
		break;
	case '5': // SmallBlock
		curPoints = this->smallBlock.getCurrentBodyPoints();
		if (shouldErase) {
			this->updateValueByPoints(curPoints, 2, BoardCellType::Empty);
		}
		else {
			this->updateValueByPoints(curPoints, 2, BoardCellType::SmallBlock);
		}
		break;
	case '6': // BigBlock
		curPoints = this->bigBlock.getCurrentBodyPoints();
		if (shouldErase) {
			this->updateValueByPoints(curPoints, 6, BoardCellType::Empty);
		}
		else {
			this->updateValueByPoints(curPoints, 6, BoardCellType::BigBlock);
		}
		break;
	}

}
void Board::updateValueByPoints(const Point* points, int size, BoardCellType cellType){
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

bool Board::shouldShipBeExploed() {
	Point curBlockPoint = this->bigBlock.getCurrentBlockPoint();
	int curBlockPointY = curBlockPoint.getYPoint();
	int curBlockPointX = curBlockPoint.getXPoint();

	if (this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX)) == BoardCellType::SmallShip
		&& this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1)) == BoardCellType::SmallShip) {
		return true;
	}
	else {
		return false;
	}

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

bool Board::isSmallShipVictoryMove() {
	return this->isSmallShipNextMoveEQCellType(BoardCellType::Exit);
}

bool Board::isBigShipVictoryMove() {
	return this->isBigShipNextMoveEQCellType(BoardCellType::Exit);
}

bool Board::isSmallShipValidMove() {
	return this->isSmallShipNextMoveEQCellType(BoardCellType::Empty);
}

bool Board::isBigShipValidMove() {
	return this->isBigShipNextMoveEQCellType(BoardCellType::Empty);
}

bool Board::isSmallShipNextMoveEQCellType(BoardCellType cellType) {
	Point curShipPoint = this->smallShip.getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();

	Direction dir = this->smallShip.getDirection();

	switch ((int)dir) {
	case 0: // UP
		if ((this->getValueByIndex(Point(curShipPointY - 1, curShipPointX)) == cellType
			&& this->getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1)) == cellType)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((this->getValueByIndex(Point(curShipPointY + 1, curShipPointX)) == cellType
			&& this->getValueByIndex(Point(curShipPointY + 1, curShipPointX + 1)) == cellType)) {
			return true;
		}

		break;
	case 2: // LEFT
		if (this->getValueByIndex(Point(curShipPointY, curShipPointX - 1)) == cellType) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (this->getValueByIndex(Point(curShipPointY, curShipPointX + 2)) == cellType) {
			return true;
		}

		break;
	}
	return false;
}

bool Board::isBigShipNextMoveEQCellType(BoardCellType cellType) {
	Point curShipPoint = this->bigShip.getCurrentShipPoint();
	int curShipPointY = curShipPoint.getYPoint();
	int curShipPointX = curShipPoint.getXPoint();

	Direction dir = this->bigShip.getDirection();

	switch ((int)dir) {
	case 0: // UP
		if ((this->getValueByIndex(Point(curShipPointY - 1, curShipPointX)) == cellType
			&& this->getValueByIndex(Point(curShipPointY - 1, curShipPointX + 1)) == cellType)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((this->getValueByIndex(Point(curShipPointY + 2, curShipPointX)) == cellType
			&& this->getValueByIndex(Point(curShipPointY + 2, curShipPointX + 1)) == cellType)) {
			return true;
		}

		break;
	case 2: // LEFT
		if ((this->getValueByIndex(Point(curShipPointY, curShipPointX - 1)) == cellType
			&& this->getValueByIndex(Point(curShipPointY + 1, curShipPointX - 1)) == cellType)) {
			return true;
		}

		break;
	case 3: // RIGHT
		if ((this->getValueByIndex(Point(curShipPointY, curShipPointX + 2)) == cellType
			&& this->getValueByIndex(Point(curShipPointY + 1, curShipPointX + 2)) == cellType)) {
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

	if ((this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX)) == BoardCellType::Empty
		&& this->getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1)) == BoardCellType::Empty) || this->shouldShipBeExploed()) {
		results[counter] = BlockSize::Big;
		counter++;
	}
}

void Board::dropBlocks(const BlockSize(&fallingBlocks)[2]) {
	for (BlockSize curBlockSize : fallingBlocks) {
		if (curBlockSize == BlockSize::Small) {
			if (this->isBlockValidMove(BlockSize::Small, Direction::Down)) {
				this->smallBlockMove(Direction::Down);
			}
		}
		else if (curBlockSize == BlockSize::Big) {
			if (this->isBlockValidMove(BlockSize::Big, Direction::Down)) {
				this->bigBlockMove(Direction::Down);
			}
			if (this->shouldShipBeExploed()) {
				this->isLoss = true;
			}
		}
	}
}

void Board::updateExitsStatus(ShipSize shipSize) {
	Point curPoint;
	if (shipSize == ShipSize::Small) {
			this->exitsStatus[0] = true;
			this->isSmallShipMove = false;
	}
	else {
			this->exitsStatus[1] = true;
			this->isSmallShipMove = true;
	}
}

void Board::updateVictory() {
	bool isVictory = true;
	for (bool status : this->exitsStatus) {
		if (!status) {
			isVictory = false;
		}
	}
	this->isVictory = isVictory;
}

void clearLine(int lineNumber) {
	gotoxy(0, lineNumber);
	for (int i = 0; i < Bounderies::cols; i++) {
		std::cout << ' ';
	}
}
void Board::printStatus(int lives) {
	clearLine(24);
	setTextColor(Color::WHITE);
	this->printTimer();
	this->printShipTurn();
	this->printRemainingLives(lives);

}
void Board::printTimer() {
	gotoxy(0, 24);
	std::cout << "- " << "Time left: " << this->time  << std::endl;
}

void Board::printShipTurn() {
	gotoxy(20, 24);
	string activeShip = this->isSmallShipMove ? "Small Ship" : "Big Ship";
	std::cout << "- " << "Active ship: " << activeShip  << std::endl;
}

void Board::printRemainingLives(int lives) {
	gotoxy(47, 24);
	
	std::cout << "- " << "Remaining lives: " << lives  << std::endl;
}
