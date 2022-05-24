#include "board.h" 

Board::~Board() {
	this->boardGame.clear();
	this->ghosts.clear();
	this->blocks.clear();
	this->stepsFile.closeFile();
	this->resultFile.closeFile();
}

Board::Board(bool isWithColors,int time,BoardCellType controlledShip,string _boardGame, int legendLocation, int numOfBlocks, int numOfGhosts, std::string screenNumber, bool isFileMode, bool isSaveMode):legened(Legened(legendLocation, isWithColors)), isWithColors(isWithColors), isSmallShipMove(controlledShip == BoardCellType::SmallShip), time(time), numOfBlocks(numOfBlocks), numOfGhosts(numOfGhosts), screenNumber(screenNumber), isFileMode(isFileMode), isSaveMode(isSaveMode), stepsFile(true), resultFile(false){
	vector<bool> blocksExists(numOfBlocks);
	int counterNumOfBlocks;
	bool isBigShipExists = false;
	bool isSmallShipExists = false;
	int cur;
	int ghostCounter = 0;

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
			if (this->boardGame[x][y] == (char)BoardCellType::HorizontalGhost) {
				this->ghosts.push_back(make_shared<Ghost>(Ghost('%', Color::YELLOW, Point(x, y), isWithColors, GhostType::Horizontal, Direction::Right)));
				ghostCounter++;
			}
			if (this->boardGame[x][y] == (char)BoardCellType::VerticalGhost) {
				this->ghosts.push_back(make_shared<Ghost>(Ghost('!', Color::YELLOW, Point(x, y), isWithColors, GhostType::Vertical, Direction::Up)));
				ghostCounter++;
			}
			if (this->boardGame[x][y] >= '1' && this->boardGame[x][y] <= parseIntToChar(numOfBlocks)) {
				if (!blocksExists[parseCharToInt(this->boardGame[x][y])-1] ) {
					this->blocks.push_back(Block(this->boardGame, x,  y, numOfBlocks, '*'+x+y, Color::LIGHTGREEN, Point(x,y), isWithColors));
					blocksExists[parseCharToInt(this->boardGame[x][y])-1] = true;
				}
			}
			if (this->boardGame[x][y] == (char)BoardCellType::WonderGhost) {
				this->ghosts.push_back(make_shared<WonderGhost>(WonderGhost('*', Color::YELLOW, Point(x, y), isWithColors, this->boardGame)));
				ghostCounter++;
			}
		}
	}
}

bool Board::play(bool& isEsc, const int lives) {
	bool shouldExitLoop = false;
	bool isFirstEsc = false;
	char key = 0;
	this->initBoard();
	while (key != ESC_SECOND && !shouldExitLoop) {
		key = 0;
		isFirstEsc = this->runTheGame(lives);
		if (isFirstEsc) {
			this->legened.printEscOptions();
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
		isEsc = true;
	}

	setTextColor(Color::WHITE);
	clear_screen();
	return this->isVictory;
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
		this->ghosts[i]->draw(this->boardGame);
	}
	for (int i = 0; i < this->blocks.size(); i++) {
		this->blocks[i].draw(this->boardGame);
	}
}

bool Board::runTheGame(const  int lives) {
	bool isHittedOnce = false;
	bool isSwitched = false;
	char key = 0;
	int stepCounter = 0;
	Point wonderGhostCurrentPoint;

	if (isFileMode) {
		this->stepsFile.openFile(this->screenNumber, isSaveMode);
		this->resultFile.openFile(this->screenNumber, isSaveMode);
	}

	while (key != ESC && !this->isVictory && this->time > 0 && !this->isLoss) {
		stepCounter++;
		vector<int> dropBlockIndexes;
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
					for (int i = 0; i < this->ghosts.size(); i++) {
						string ghostType = typeid(this->ghosts[i]).name();
						if (ghostType.compare(typeid(WonderGhost).name())) {
							wonderGhostCurrentPoint = this->ghosts[i]->getCurrentPoint();
						}
					}
					
					Direction nextDirection = getDirectionByKey(key);
					if (this->isFileMode && this->isSaveMode) {
						this->stepsFile.writeToStepsFile(stepCounter, wonderGhostCurrentPoint, this->isSmallShipMove ? nextDirection : Direction::None, !this->isSmallShipMove ? nextDirection : Direction::None);
					}
					if (this->isSmallShipMove) {
						if (isSwitched) {
							isSwitched = false;
						}
						this->smallShip.setDirection(nextDirection);
						this->smallShipMove();
						dropBlockIndexes = getFallingBlockIndexes();
						dropBlocks(dropBlockIndexes);
					}
					else {
						if (isSwitched) {
							isSwitched = false;
						}
						this->bigShip.setDirection(nextDirection);
						this->bigShipMove();
						dropBlockIndexes = getFallingBlockIndexes();
						dropBlocks(dropBlockIndexes);
					}
				}
			}
		}
		else if (isHittedOnce && !this->isLoss) {
			this->moveGhosts();
			if (this->isSmallShipMove && !isSwitched) {
					this->smallShipMove();
					dropBlockIndexes = getFallingBlockIndexes();
					dropBlocks(dropBlockIndexes);
			}
			else if (!isSwitched) {
				this->bigShipMove();
				dropBlockIndexes = getFallingBlockIndexes();
				dropBlocks(dropBlockIndexes);

			}
		}
		this->updateVictory();
		if (isHittedOnce) {
			this->time--;
		}
		this->legened.printStatus(lives, time, this->isSmallShipMove);
		Sleep(200);
	}

	if (key == ESC) {
		return true;
	}
	else {
		if(this->isFileMode && this->isSaveMode){
			this->resultFile.writeToResultFile(stepCounter, this->isLoss, this->isVictory);
		}
		
		return false;
	}
}


void Board::moveGhosts() {
	for (int i = 0; i < this->ghosts.size(); i++) {
		if (this->ghosts[i]->isValidMoveAuto(this->boardGame)) {
			this->ghosts[i]->moveAuto(this->boardGame);
			if (this->ghosts[i]->isHitShip(this->boardGame)) {
				this->isLoss = true;
			}
		}
		else {
			if (this->ghosts[i]->getDirection() == Direction::Left) {
				this->ghosts[i]->setDirection(Direction::Right);
			} else if(this->ghosts[i]->getDirection() == Direction::Right) {
				this->ghosts[i]->setDirection(Direction::Left);
			} else if (this->ghosts[i]->getDirection() == Direction::Up) {
				this->ghosts[i]->setDirection(Direction::Down);
			} else if (this->ghosts[i]->getDirection() == Direction::Down) {
				this->ghosts[i]->setDirection(Direction::Up);
			}
		
			this->ghosts[i]->moveAuto(this->boardGame);
			if (this->ghosts[i]->isHitShip(this->boardGame)) {
				this->isLoss = true;
			}
		}
	}
};

void Board::smallShipMove() {
	bool isBlockCanMove = true;
	Direction dir = this->smallShip.getDirection();
	int blockIndexToMove = -1;

	if ((this->smallShip.isShipValidMove(this->boardGame) || this->smallShip.isShipValidBlockMove(blockIndexToMove, this->boardGame, this->blocks)) && !this->exitsStatus[0]) {
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
			this->smallShip.move(dir, this->boardGame);
		}
	}

	if (this->smallShip.isShipVictoryMove(this->boardGame)) {
		this->updateExitsStatus(ShipSize::Small);
		this->smallShip.erase(this->boardGame);
	}
}

void Board::bigShipMove() {
	bool isBlockCanMove = true;
	Direction dir = this->bigShip.getDirection();
	int blockIndexToMove = -1;

	if ((this->bigShip.isShipValidMove(this->boardGame) || this->bigShip.isShipValidBlockMove(blockIndexToMove, this->boardGame, this->blocks)) && !this->exitsStatus[1]) {
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
			this->bigShip.move(dir, this->boardGame);
		}
	}

	if (this->bigShip.isShipVictoryMove(this->boardGame)) {
		this->updateExitsStatus(ShipSize::Big);
		this->bigShip.erase(this->boardGame);
	}
}

bool Board::shouldShipBeExploed() const {
	for (int i = 0; i < this->blocks.size(); i++) {
		if (this->bigShip.shouldBlockExplodeShip(this->boardGame, this->blocks[i])) {
			return true;
		}
		if (this->smallShip.shouldBlockExplodeShip(this->boardGame, this->blocks[i])) {
			return true;
		}
	}
	return false;
}

const vector<int> Board::getFallingBlockIndexes() const {
	vector<int> blockIndexes;
	Point curBlockPoint;
	int curBlockPointY, curBlockPointX;

	for (int i = 0; i < this->blocks.size(); i++) {
		if (this->blocks[i].shouldBlockFall(this->boardGame)) {
			blockIndexes.push_back(i);
		}
	}
	return blockIndexes;
}

void Board::dropBlocks(const vector<int> blockIndexes) {
	for (int i = 0; i < blockIndexes.size(); i++) {
		if (this->blocks[blockIndexes[i]].isValidMove(Direction::Down, this->boardGame)) {
			this->blocks[blockIndexes[i]].move(Direction::Down, this->boardGame);
		}
		if (this->shouldShipBeExploed()) {
			this->isLoss = true;
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


