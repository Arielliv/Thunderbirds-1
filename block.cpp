#include "block.h"

Block& Block::operator=(const Block& b) {
	this->startPoint = b.startPoint;
	this->figure = b.figure;
	this->color = b.color;
	this->isEmpty = b.isEmpty;
	this->isWithColors = b.isWithColors;
	this->body = b.body;
	return *this;
}

Block::Block(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks, char figure, Color color, Point startPoint, bool isWithColors):isEmpty(false),figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	this->createBlockRec(boardGame, x, y, numOfBlocks);
}

void Block::createBlockRec(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks) {
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

Block::Block(int blockSize, char figure, Color color, Point startPoint, bool isWithColors):isEmpty(false),  figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	if (blockSize == 2) {
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
		for (int i = 0; i< this->body.size(); i++) {
			
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}
		for (int i = 0; i < this->body.size(); i++) {
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}
		updateValueByPoints(this->body, this->body.size(), this->figure, boardGame);
}


void Block::draw(vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(figure);
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	}

	updateValueByPoints(this->body, this->body.size(), this->figure, boardGame);
}

Block::~Block() {
	this->body.clear();
}

const Point& Block::getCurrentBlockPoint() const{
	return this->body[0];
}

const vector<Point>& Block::getCurrentBodyPoints() const {
	return this->body;
}

bool Block::isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->body.size(); i++) {
		Point curBlockPoint = this->body[i];
		int curBlockPointY = curBlockPoint.getYPoint();
		int curBlockPointX = curBlockPoint.getXPoint();

		switch (dir) {
		case Direction::Up: 
			if (getValueByIndex(Point(curBlockPointY -1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY - 1, curBlockPointX), boardGame) != this->figure) {
				return false;
			}
			break;
		case Direction::Down: 
			if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != this->figure) {
				return false;
			}

			break;
		case Direction::Left: 
			if (getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) != this->figure) {
				return false;
			}

			break;
		case Direction::Right: 
			if (getValueByIndex(Point(curBlockPointY, curBlockPointX + 1), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY, curBlockPointX + 1), boardGame) != this->figure) {
				return false;
			}

			break;
		}
	}
	return true;
}

int Block::getBlockSize() const {
	return this->body.size();
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