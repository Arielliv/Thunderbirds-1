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
"10000000007000000000000011000000000000000000000000000000000000000000000000000001"
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

Board::~Board() {
	this->boardGame.clear();
}

Board& Board::operator=(const Board& b) {
	this->bigShip = b.bigShip;
	this->smallShip = b.smallShip;
	this->isVictory = b.isVictory;
	this->isSmallShipMove = b.isSmallShipMove;
	this->time = b.time;
	this->isLoss = b.isLoss;
	this->isWithColors = b.isWithColors;
	this->exitsStatus = b.exitsStatus;
	this->ghosts = b.ghosts;
	this->blocks = b.blocks;
	this->boardGame = b.boardGame;
	return *this;
}

Board::Board(bool isWithColors,int time,BoardCellType controlledShip,string _boardGame, int legendLocation, int numOfBlocks):isWithColors(isWithColors), isSmallShipMove(controlledShip == BoardCellType::SmallShip), time(time), numOfBlocks(numOfBlocks) { 
	vector<bool> blocksExists(numOfBlocks);
	int counterNumOfBlocks;
	bool isBigShipExists = false;
	bool isSmallShipExists = false;
	int cur;
	for (int x = 0; x < (int)Bounderies::rows; x++) {
		vector <char> row;
		for (int y = 0; y < (int)Bounderies::cols; y++) {
			cur = x * (int)Bounderies::cols + y;
			row.push_back(_boardGame[cur]);
		}
		this->boardGame.push_back(row);
	}

	for (int x = 0; x < (int)Bounderies::rows; x++) {
		for (int y = 0; y < (int)Bounderies::cols; y++) {
			if (this->boardGame[x][y] == (char)BoardCellType::BigShip && !isBigShipExists) {
				this->bigShip = Ship(ShipSize::Big, '@', Color::LIGHTCYAN, Point(x, y), isWithColors);
				isBigShipExists = true;
			}
			if (this->boardGame[x][y] == (char)BoardCellType::SmallShip && !isSmallShipExists) {
				this->smallShip = Ship(ShipSize::Small, '&', Color::LIGHTMAGENTA, Point(x, y), isWithColors);
				isSmallShipExists = true;
			}
			if (this->boardGame[x][y] == (char)BoardCellType::Ghost) {
				this->ghosts.push_back(Ghost('%', Color::YELLOW, Point(x, y), isWithColors, GhostType::Horizontal, Direction::Right));
			}
			if (this->boardGame[x][y] >= '1' && this->boardGame[x][y] <= parseIntToChar(numOfBlocks)) {
				if (!blocksExists[parseCharToInt(this->boardGame[x][y])-1] ) {
					this->blocks.push_back(Block(this->boardGame, x,  y, numOfBlocks, '*'+x+y, Color::LIGHTGREEN, Point(x,y), isWithColors));
					blocksExists[parseCharToInt(this->boardGame[x][y])-1] = true;
				}
			}
		}
	}
}

void Board::printBoard() const {
	clear_screen();
	for (int x = 0; x < Bounderies::rows; x++) {
		for (int y = 0; y < Bounderies::cols; y++) {
			char currentCellType = getValueByIndex(Point(x, y), this->boardGame);
			Point currentPoint = Point(y, x);
			if (currentCellType == (char)BoardCellType::Wall) {
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
	this->bigShip.draw(this->boardGame);
	this->smallShip.draw(this->boardGame);
	for (int i = 0; i < this->ghosts.size(); i++) {
		this->ghosts[i].draw(this->boardGame);
	}
	for (int i = 0; i < this->blocks.size(); i++) {
		this->blocks[i].draw(this->boardGame);
	}
}

bool Board::runTheGame(const  int lives) {
	bool isHittedOnce = false;
	bool isSwitched = false;
	char key = 0;

	while (key != ESC && !this->isVictory && this->time > 0 && !this->isLoss) {
		if (_kbhit()) {
			key = _getch();
			if (key != ESC) {
				isHittedOnce = true;
			}
			if (getKeyByChar(key) == Keys::SwitchSmall) {
				this->isSmallShipMove = true;
				isSwitched = true;
			}
			else if (getKeyByChar(key) == Keys::SwitchBig) {
				this->isSmallShipMove = false;
				isSwitched = true;
			}
			else {
				if (key != ESC) {
					Direction nextDirection = getDirectionByKey(key);
					if (this->isSmallShipMove) {
						if (isSwitched) {
							isSwitched = false;
						}
						this->smallShip.setDirection(nextDirection);
						this->smallShipMove();
						BlockSize curFallingBlocks[2];
						getFallingBlockTypes(curFallingBlocks);
						dropBlocks(curFallingBlocks);
					}
					else {
						if (isSwitched) {
							isSwitched = false;
						}
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
			this->moveGhosts();
			if (this->isSmallShipMove && !isSwitched) {
					this->smallShipMove();
					BlockSize curFallingBlocks[2];
					getFallingBlockTypes(curFallingBlocks);
					dropBlocks(curFallingBlocks);
			}
			else if (!isSwitched) {
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

void Board::moveGhosts() {
	for (int i = 0; i < this->ghosts.size(); i++) {
		if (this->ghosts[i].isValidMove(this->boardGame)){
			this->ghosts[i].move(this->boardGame);
			if (this->ghosts[i].isHitShip(this->boardGame)) {
				this->isLoss = true;
			}
		}
		else {
			if (this->ghosts[i].getDirection() == Direction::Left) {
				this->ghosts[i].setDirection(Direction::Right);
			}
			else {
				this->ghosts[i].setDirection(Direction::Left);
			}
			this->ghosts[i].move(this->boardGame);
			if (this->ghosts[i].isHitShip(this->boardGame)) {
				this->isLoss = true;
			}
		}
	}
};

bool Board::play(bool *isEsc, const int lives) {
	bool shouldExitLoop = false;
	bool isFirstEsc = false;
	char key = 0;
	this->initBoard();
	while (key != ESC_SECOND && !shouldExitLoop) {
		key = 0;
		isFirstEsc = this->runTheGame(lives);
		if (isFirstEsc) {
			this->printEscOptions();
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
	int blockIndexToMove = -1;

	if ((this->isShipValidMove(ShipSize::Small) || this->smallShip.isShipValidBlockMove(blockIndexToMove, this->boardGame, this->blocks)) && !this->exitsStatus[0]) {
		if (this->smallShip.isShipValidBlockMove(blockIndexToMove, this->boardGame, this->blocks)) {
			//small block valid move
			if (blockIndexToMove != -1 && this->blocks[blockIndexToMove].isValidMove(dir, this->boardGame)) {
				isBlockCanMove = true;
				this->blocks[blockIndexToMove].move(dir, this->boardGame);
			}
			else {
				isBlockCanMove = false;
			}
		}
		if (isBlockCanMove) {
			this->smallShip.move(this->boardGame);	
		}
	}

	if (this->isSmallShipVictoryMove()) {
		this->updateExitsStatus(ShipSize::Small);
		this->smallShip.erase(this->boardGame);
	}
}

void Board::bigShipMove() {
	bool isBlockCanMove = true;
	Direction dir = this->bigShip.getDirection();
	int blockIndexToMove = -1;

	if ((this->isShipValidMove(ShipSize::Big) || this->bigShip.isShipValidBlockMove(blockIndexToMove, this->boardGame, this->blocks)) && !this->exitsStatus[1]) {
		if (this->bigShip.isShipValidBlockMove(blockIndexToMove, this->boardGame, this->blocks)) {
			if (blockIndexToMove != -1) {
				// smallBlockValidMove
				if (this->blocks[blockIndexToMove].isValidMove(dir, this->boardGame)) {
					isBlockCanMove = true;
					this->blocks[blockIndexToMove].move(dir, this->boardGame);
				}
				else {
					isBlockCanMove = false;
				}

			}
		}
		if (isBlockCanMove) {
			this->bigShip.move(this->boardGame);
		}
	}

	if (this->isBigShipVictoryMove()) {
		this->updateExitsStatus(ShipSize::Big);
		this->bigShip.erase(this->boardGame);
	}
}

bool Board::isShipValidMove(const ShipSize shipSize) const {
	if (shipSize == ShipSize::Small) {
		return this->isSmallShipValidMove();
	}
	else {
		return this->isBigShipValidMove();
	}
}

bool Board::shouldShipBeExploed() const {
	for (int i = 0; i < numOfBlocks; i++) {
		if (this->blocks[i].getBlockSize() == BlockSize::Big) {
			Point curBlockPoint = this->blocks[i].getCurrentBlockPoint();
			int curBlockPointY = curBlockPoint.getYPoint();
			int curBlockPointX = curBlockPoint.getXPoint();

			if (getValueByIndex(Point(curBlockPointY + 3, curBlockPointX), this->boardGame) == (char)BoardCellType::SmallShip
				|| getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1), this->boardGame) == (char)BoardCellType::SmallShip) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool Board::isSmallShipVictoryMove() const {
	return this->smallShip.isNextMoveEQCellType(BoardCellType::Exit, this->boardGame);
}

bool Board::isBigShipVictoryMove() const {
	return this->bigShip.isNextMoveEQCellType(BoardCellType::Exit, this->boardGame);
}

bool Board::isSmallShipValidMove() const {
	return this->smallShip.isNextMoveEQCellType(BoardCellType::Empty, this->boardGame);
}

bool Board::isBigShipValidMove() const {
	return this->bigShip.isNextMoveEQCellType(BoardCellType::Empty, this->boardGame);
}

void Board::getFallingBlockTypes(BlockSize* results) const {
	Point curBlockPoint;
	int curBlockPointY, curBlockPointX, counter = 0;

	for (int i = 0; i < numOfBlocks; i++) {
		this->blocks[i].getCurrentBlockPoint();
		curBlockPointY = curBlockPoint.getYPoint();
		curBlockPointX = curBlockPoint.getXPoint();
		if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), this->boardGame) == (char)BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY + 1, curBlockPointX + 1), this->boardGame) == (char)BoardCellType::Empty) {
			results[counter] = BlockSize::Small;
			counter++;
		}

	}
}

void Board::dropBlocks(const BlockSize(&fallingBlocks)[2]) {
	for (BlockSize curBlockSize : fallingBlocks) {
		if (curBlockSize == BlockSize::Small) {
			for (int i = 0; i < numOfBlocks; i++) {
				if (this->blocks[i].isValidMove(Direction::Down, this->boardGame)) {
					this->blocks[i].move(Direction::Down, this->boardGame);
				}
				if (this->shouldShipBeExploed()) {
					this->isLoss = true;
				}
			}
		}
	}
}

void Board::updateExitsStatus(const ShipSize shipSize) {
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

void clearLine(const int lineNumber) {
	gotoxy(0, lineNumber);
	for (int i = 0; i < Bounderies::cols; i++) {
		std::cout << ' ';
	}
}

void Board::printStatus(const int lives) const {
	clearLine(23);

	if (this->isWithColors) {
		setTextColor(Color::YELLOW);
	}

	this->printTimer();
	this->printShipTurn();
	this->printRemainingLives(lives);

}
void Board::printTimer() const {
	gotoxy(8, 23);
	std::cout << "| " << "Time left: " << this->time  << std::endl;
}

void Board::printShipTurn() const {
	gotoxy(28, 23);
	string activeShip = this->isSmallShipMove ? "Small" : "Big";
	std::cout << "| " << "Active ship: " << activeShip  << std::endl;
}

void Board::printRemainingLives(int lives) const {
	gotoxy(50, 23);
	std::cout << "| " << "Remaining lives: " << lives  << std::endl;
}

void Board::printEscOptions() const {
	clearLine(23);
	gotoxy(13, 23);
	if (this->isWithColors) {
		setTextColor(Color::LIGHTRED);
	}
	std::string const escOptions = "--- To exit press 9, to unpause press ESC ---";
	std::cout << escOptions << std::endl;
}
