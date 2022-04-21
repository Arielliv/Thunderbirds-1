#pragma once

#include "color.h"
#include "point.h"
#include "constants.h"
#include "boardUtils.h"
#include "utils.h"
#include <vector>

class Block
{
	Point startPoint = Point(1, 1);
	char figure;
	Color color;
	vector<Point> body;
	bool isWithColors = false;
	bool isEmpty = true;

private:
	void createBlockRec(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks);
	bool isPointInsideBody(Point p);
public:
	Block() {};
	~Block();
	Block(int blockSize,char figure, Color color, Point startPoint, bool isWithColors);
	Block(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks,char figure, Color color, Point startPoint, bool isWithColors);
	Block& operator=(const Block& b);
	const Point& getCurrentBlockPoint() const;
	const vector<Point>& getCurrentBodyPoints() const;
	void move(const Direction direction, vector<vector<char>>& boardGame);
	void draw(vector<vector<char>>& boardGame) const;
	int getBlockSize() const;
	bool isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const;
	char getFigure()const;
	bool getIsEmpty()const;
	bool shouldBlockFall(const vector<vector<char>>& boardGame)const;
};