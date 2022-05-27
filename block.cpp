#include "block.h"

Block::Block(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks, char figure, Color color, Point startPoint, bool isWithColors, bool isSilent) :BoardGameTool( figure, color, startPoint, isWithColors, isSilent){
	this->createBlockRec(boardGame, x, y, numOfBlocks);
}

void Block::createBlockRec(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks) {
	if (boardGame[x][y] >= '1' && boardGame[x][y] <= parseIntToChar(numOfBlocks)) {
		Point newP = Point(y, x);
		if (this->isPointInsideBody(newP)) {
			return;
		}
		this->pushToBody(newP);
		this->createBlockRec(boardGame, x + 1, y, numOfBlocks);
		this->createBlockRec(boardGame, x - 1, y, numOfBlocks);
		this->createBlockRec(boardGame, x, y + 1, numOfBlocks);
		this->createBlockRec(boardGame, x, y - 1, numOfBlocks);
	}
}

bool Block::isPointInsideBody(Point p) {
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getBody()[i] == p) {
			return true;
		}
	}
	return false;
}

bool Block::shouldBlockFall(const vector<vector<char>>& boardGame) const {

	for (int i = 0; i < this->getSize(); i++) {
		const Point curBlockPoint = this->getBody()[i];
		int curBlockPointY = curBlockPoint.getYPoint();
		int curBlockPointX = curBlockPoint.getXPoint();

		if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
			getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != this->getFigure() &&
			getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != (char)BoardCellType::SmallShip
			) {
			return false;
		}
	}
	return true;
};