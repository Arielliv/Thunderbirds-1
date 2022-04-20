#pragma once

#include "color.h"
#include "point.h"
#include "constants.h"
#include "boardUtils.h"
#include "utils.h"
#include <vector>

enum class  BlockSize { Small = 2, Big = 6 };

class Block
{
	BlockSize blockSize;
	Point startPoint = Point(1, 1);
	char figure;
	Color color;
	vector<Point> body;
	bool isWithColors = false;
	bool isEmpty = true;

private:
	void createBlockRec(vector<vector<char>>& boardGame, int x, int y, int numOfBlocks);
	bool isPointInsideBody(Point p);
public:
	Block() {};
	Block(BlockSize blockSize, char figure, Color color, Point startPoint, bool isWithColors);
	Block(vector<vector<char>>& boardGame, int x, int y, int numOfBlocks,char figure, Color color, Point startPoint, bool isWithColors);
	Block& operator=(const Block& b);
	Point getCurrentBlockPoint() const;
	const vector<Point> getCurrentBodyPoints() const;
	void move(const Direction direction, vector<vector<char>>& boardGame);
	void draw(vector<vector<char>>& boardGame) const;
	~Block();
	BlockSize getBlockSize() const;
	bool isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const;
	char getFigure()const;
	bool getIsEmpty()const;
};