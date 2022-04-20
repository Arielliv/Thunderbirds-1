#include "block.h"

Block& Block::operator=(const Block& b) {
	this->blockSize = b.blockSize;
	this->startPoint = b.startPoint;
	this->figure = b.figure;
	this->color = b.color;
	this->isEmpty = b.isEmpty;
	this->isWithColors = b.isWithColors;
	this->body = b.body;
	return *this;
}

Block::Block(vector<vector<char>>& boardGame, int x, int y, int numOfBlocks, char figure, Color color, Point startPoint, bool isWithColors):isEmpty(false),figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	this->createBlockRec(boardGame, x, y, numOfBlocks);
	if (this->body.size() == (int)BlockSize::Small) {
		this->blockSize = BlockSize::Small;
	}
	else {
		this->blockSize = BlockSize::Big;
	}
}

void Block::createBlockRec(vector<vector<char>>& boardGame, int x, int y, int numOfBlocks) {
	if (boardGame[x][y] >= '1' && boardGame[x][y] <= parseIntToChar(numOfBlocks)) {
		Point newP = Point(y, x);
		if (this->isPointInsideBody(newP)) {
			return;
		}
		this->body.push_back(newP);
		this->createBlockRec(boardGame, x + 1, y, numOfBlocks);
		this->createBlockRec(boardGame, x -1, y, numOfBlocks);
		this->createBlockRec(boardGame, x , y+1, numOfBlocks);
		this->createBlockRec(boardGame, x, y-1, numOfBlocks);
	}
}

Block::Block(BlockSize blockSize, char figure, Color color, Point startPoint, bool isWithColors):isEmpty(false), blockSize(blockSize), figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	if (blockSize == BlockSize::Small) {
		for (int i = 0; i < 2; i++) {
			this->body.push_back(Point(this->startPoint.getXPoint() + i, this->startPoint.getYPoint()));
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->body.push_back(Point(this->startPoint.getXPoint() + j, this->startPoint.getYPoint() + i));
			}
		}
	}
}

bool Block::isPointInsideBody(Point p) {
	for (int i = 0; i < this->body.size(); i++) {
		if (this->body[i] == p) {
			return true;
		}
	}
	return false;
}

void Block::move(const Direction direction, vector<vector<char>>& boardGame) {
	updateValueByPoints(this->body, this->body.size(), (char)BoardCellType::Empty, boardGame);
		for (std::size_t i = 0; i< this->body.size(); i++) {
			
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}
		for (std::size_t i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}
		updateValueByPoints(this->body, this->body.size(), this->figure, boardGame);
}


void Block::draw(vector<vector<char>>& boardGame) const {
	for (std::size_t i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(figure);
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	}

	updateValueByPoints(this->body, (int)this->blockSize, this->figure, boardGame);
}

Block::~Block() {
	this->body.clear();
}

Point Block::getCurrentBlockPoint() const{
	return Point(this->body[0]);
}

const vector<Point> Block::getCurrentBodyPoints() const {
	return this->body;
}

bool Block::isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->body.size(); i++) {
		Point curBlockPoint = this->body[i];
		int curBlockPointY = curBlockPoint.getYPoint();
		int curBlockPointX = curBlockPoint.getXPoint();
		switch ((int)dir) {
		case 0: // UP
			if (getValueByIndex(Point(curBlockPointY -1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY - 1, curBlockPointX), boardGame) != this->figure) {
				return false;
			}
			break;
		case 1: // DOWN
			if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != this->figure) {
				return false;
			}

			break;
		case 2: // LEFT
			if (getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) != this->figure) {
				return false;
			}

			break;
		case 3: // RIGHT
			if (getValueByIndex(Point(curBlockPointY, curBlockPointX + 1), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY, curBlockPointX + 1), boardGame) != this->figure) {
				return false;
			}

			break;
		}
	}
	return true;
}

BlockSize Block::getBlockSize() const {
	return this->blockSize;
}
char Block::getFigure()const {
	return this->figure;
}

bool Block::getIsEmpty()const {
	return this->isEmpty;
}

bool Block::shouldBlockFall(const vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->body.size(); i++) {
		Point curBlockPoint = this->body[i];
		int curBlockPointY = curBlockPoint.getYPoint();
		int curBlockPointX = curBlockPoint.getXPoint();

		if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
			getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != this->figure &&
			getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != (char)BoardCellType::SmallShip
			) {
			return false;
		}
	}
	return true;
};