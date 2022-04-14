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

	for (int i = 0; i < b.ghosts.size(); i++) {
		this->ghosts[i] = b.ghosts[i];
	}
	
	for (int x = 0; x < (int)Bounderies::rows; x++) {
		for (int y = 0; y < (int)Bounderies::cols; y++) {
			boardGame[x][y] = b.boardGame[x][y];
		}
	}
	return *this;
}

Board::Board(bool isWithColors):bigShip(Ship(ShipSize::Big, '@', Color::LIGHTCYAN, Point(34, 3), isWithColors)), smallShip(Ship(ShipSize::Small, '&', Color::LIGHTMAGENTA, Point(5, 5), isWithColors)), smallBlock(Block(BlockSize::Small, '^', Color::LIGHTGREEN, Point(23,7), isWithColors)), bigBlock(Block(BlockSize::Big, '~', Color::CYAN, Point(51, 10), isWithColors)), isWithColors(isWithColors) {
	int cur;
	
	for (int x = 0; x < (int)Bounderies::rows; x++) {
		vector <char> row;
		for (int y = 0; y < (int)Bounderies::cols; y++) {
			cur = x * (int)Bounderies::cols + y;
			if (staticBoard[cur] == (int)BoardCellType::BigShip) {
			}
			if (staticBoard[cur] == (int)BoardCellType::Ghost) {
				this->ghosts.push_back(Ghost('%', Color::YELLOW, Point(x, y), isWithColors, GhostType::Horizontal, Direction::Right));
			}
			row.push_back(staticBoard[cur]);
		}
		this->boardGame.push_back(row);
	}
}

Board::Board(bool isWithColors,int time,BoardCellType controlledShip,string boardGame, int legendLocation):isWithColors(isWithColors), isSmallShipMove(controlledShip == BoardCellType::SmallShip), time(time) {

	//smallBlock(Block(BlockSize::Small, '^', Color::LIGHTGREEN, Point(23, 7), isWithColors))
	//bigBlock(Block(BlockSize::Big, '~', Color::CYAN, Point(51, 10), isWithColors)), 


	int cur;
	for (int x = 0; x < (int)Bounderies::rows; x++) {
		vector <char> row;
		for (int y = 0; y < (int)Bounderies::cols; y++) {
			cur = x * (int)Bounderies::cols + y;
			if (boardGame[cur] == (int)BoardCellType::BigShip && this->bigShip.isShipEmpty()) {
				this->bigShip = Ship(ShipSize::Big, '@', Color::LIGHTCYAN, Point(x, y), isWithColors);
			}
			if (boardGame[cur] == (int)BoardCellType::SmallShip && this->smallShip.isShipEmpty()) {
				this->smallShip = Ship(ShipSize::Small, '&', Color::LIGHTMAGENTA, Point(x, y), isWithColors);
			}
			if (boardGame[cur] == (int)BoardCellType::Ghost) {
				this->ghosts.push_back(Ghost('%', Color::YELLOW, Point(x, y), isWithColors, GhostType::Horizontal, Direction::Right));
			}
			row.push_back(boardGame[cur]);
		}
		this->boardGame.push_back(row);
	}
}

void Board::printBoard() const {
	clear_screen();
	for (int x = 0; x < Bounderies::rows; x++) {
		for (int y = 0; y < Bounderies::cols; y++) {
			BoardCellType currentCellType = getValueByIndex(Point(x, y), this->boardGame);
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
	this->bigShip.draw(this->boardGame);
	this->smallShip.draw(this->boardGame);
	this->bigBlock.draw(this->boardGame);
	this->smallBlock.draw(this->boardGame);
	for (int i = 0; i < this->ghosts.size(); i++) {
		this->ghosts[i].draw(this->boardGame);
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
	BoardCellType curBoardCellType = BoardCellType::Empty;

	if ((this->isShipValidMove(ShipSize::Small) || this->smallShip.isShipValidBlockMove(&curBoardCellType, this->boardGame)) && !this->exitsStatus[0]) {
		if (this->smallShip.isShipValidBlockMove(&curBoardCellType, this->boardGame)) {
			if (this->smallBlock.isValidMove(dir, this->boardGame)) {
				isBlockCanMove = true;
				this->smallBlockMove(dir);
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
	BoardCellType curBoardCellType = BoardCellType::Empty;

	if ((this->isShipValidMove(ShipSize::Big) || this->bigShip.isShipValidBlockMove(&curBoardCellType, this->boardGame)) && !this->exitsStatus[1]) {
		if (this->bigShip.isShipValidBlockMove(&curBoardCellType, this->boardGame)) {
			if (curBoardCellType == BoardCellType::SmallBlock) {
				if (this->smallBlock.isValidMove(dir, this->boardGame)) {
					isBlockCanMove = true;
					this->smallBlockMove(dir);
				}
				else {
					isBlockCanMove = false;
				}
			}
			else if (curBoardCellType == BoardCellType::BigBlock) {
				if (this->bigBlock.isValidMove(dir, this->boardGame)) {
					isBlockCanMove = true;
					this->bigBlockMove(dir);
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

void Board::smallBlockMove(const Direction dir) {
	this->smallBlock.move(dir,this->boardGame);
}

void Board::bigBlockMove(const Direction dir) {
	this->bigBlock.move(dir,this->boardGame);
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
	Point curBlockPoint = this->bigBlock.getCurrentBlockPoint();
	int curBlockPointY = curBlockPoint.getYPoint();
	int curBlockPointX = curBlockPoint.getXPoint();

	if (getValueByIndex(Point(curBlockPointY + 3, curBlockPointX), this->boardGame) == BoardCellType::SmallShip
		|| getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1), this->boardGame) == BoardCellType::SmallShip) {
		return true;
	}
	else {
		return false;
	}

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

	curBlockPoint = this->smallBlock.getCurrentBlockPoint();
	curBlockPointY = curBlockPoint.getYPoint();
	curBlockPointX = curBlockPoint.getXPoint();

	if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), this->boardGame) == BoardCellType::Empty
		&& getValueByIndex(Point(curBlockPointY + 1, curBlockPointX + 1), this->boardGame) == BoardCellType::Empty) {
		results[counter] = BlockSize::Small;
		counter++;
	}

	curBlockPoint = this->bigBlock.getCurrentBlockPoint();
	curBlockPointY = curBlockPoint.getYPoint();
	curBlockPointX = curBlockPoint.getXPoint();

	if ((getValueByIndex(Point(curBlockPointY + 3, curBlockPointX), this->boardGame) == BoardCellType::Empty
		&& getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1), this->boardGame) == BoardCellType::Empty) || this->shouldShipBeExploed()) {
		results[counter] = BlockSize::Big;
		counter++;
	}
}

void Board::dropBlocks(const BlockSize(&fallingBlocks)[2]) {
	for (BlockSize curBlockSize : fallingBlocks) {
		if (curBlockSize == BlockSize::Small) {
			if (this->smallBlock.isValidMove(Direction::Down, this->boardGame)) {
				this->smallBlockMove(Direction::Down);
			}
		}
		else if (curBlockSize == BlockSize::Big) {
			if (this->bigBlock.isValidMove(Direction::Down, this->boardGame)) {
				this->bigBlockMove(Direction::Down);
			}
			if (this->shouldShipBeExploed()) {
				this->isLoss = true;
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
