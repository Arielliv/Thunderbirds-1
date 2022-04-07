#include "block.h"

Block& Block::operator=(const Block& b) {
	this->blockSize = b.blockSize;
	this->startPoint = b.startPoint;
	this->figure = b.figure;
	this->color = b.color;
	this->isWithColors = b.isWithColors;
	
	for (int i = 0; i < b.body.size(); i++) {
		body[i] = b.body[i];
	}
	return *this;
}

Block::Block(BlockSize blockSize, char figure, Color color, Point startPoint, bool isWithColors) : blockSize(blockSize), figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
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

void Block::move(const Direction direction, vector<vector<char>>& boardGame) {
	updateValueByPoints(this->body, (int)this->blockSize, BoardCellType::Empty, boardGame);
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
		updateValueByPoints(this->body, (int)this->blockSize, this->blockSize == BlockSize::Small ? BoardCellType::SmallBlock : BoardCellType::BigBlock, boardGame);
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

	updateValueByPoints(this->body, (int)this->blockSize, this->blockSize == BlockSize::Small ? BoardCellType::SmallBlock : BoardCellType::BigBlock, boardGame);
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
	if (this->blockSize == BlockSize::Big) {
		return this->isBigBlockValidMove(dir, boardGame);
	}
	else {
		return this->isSmallBlockValidMove(dir, boardGame);
	}
}

bool Block::isSmallBlockValidMove(const Direction dir, const vector<vector<char>>& boardGame) const {
	Point curBlockPoint = this->getCurrentBlockPoint();
	int curBlockPointY = curBlockPoint.getYPoint();
	int curBlockPointX = curBlockPoint.getXPoint();

	switch ((int)dir) {
	case 0: // UP
		if ((getValueByIndex(Point(curBlockPointY - 1, curBlockPointX),boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY - 1, curBlockPointX + 1), boardGame) == BoardCellType::Empty)) {
			return true;
		}

		break;
	case 1: // DOWN
		if ((getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY + 1, curBlockPointX + 1), boardGame) == BoardCellType::Empty)) {
			return true;
		}

		break;
	case 2: // LEFT
		if (getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) == BoardCellType::Empty) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (getValueByIndex(Point(curBlockPointY, curBlockPointX + 2), boardGame) == BoardCellType::Empty) {
			return true;
		}

		break;
	}
	return false;
}

bool Block::isBigBlockValidMove(const Direction dir, const vector<vector<char>>& boardGame) const {
	Point curBlockPoint = this->getCurrentBlockPoint();
	int curBlockPointY = curBlockPoint.getYPoint();
	int curBlockPointX = curBlockPoint.getXPoint();

	switch ((int)dir) {
	case 0: // UP
		if (getValueByIndex(Point(curBlockPointY - 1, curBlockPointX),boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY - 1, curBlockPointX + 1),boardGame) == BoardCellType::Empty) {
			return true;
		}

		break;
	case 1: // DOWN
		if (getValueByIndex(Point(curBlockPointY + 3, curBlockPointX),boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY + 3, curBlockPointX + 1),boardGame) == BoardCellType::Empty) {
			return true;
		}

		break;
	case 2: // LEFT
		if (getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY + 1, curBlockPointX - 1), boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY + 2, curBlockPointX - 1), boardGame) == BoardCellType::Empty) {
			return true;
		}

		break;
	case 3: // RIGHT
		if (getValueByIndex(Point(curBlockPointY, curBlockPointX + 2), boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY + 1, curBlockPointX + 2), boardGame) == BoardCellType::Empty
			&& getValueByIndex(Point(curBlockPointY + 2, curBlockPointX + 2), boardGame) == BoardCellType::Empty) {
			return true;
		}

		break;
	}
	return false;
}
