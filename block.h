#pragma once

#include "color.h"
#include "point.h"
#include "constants.h"
#include "boardUtils.h"
#include "utils.h"
#include "boardGameTool.h"
#include <vector>

class Block : public BoardGameTool
{
	bool isEmpty = true;
private:
	void createBlockRec(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks);
	bool isPointInsideBody(Point p);
public:
	Block() {};
	Block(const vector<vector<char>>& boardGame, int x, int y, int numOfBlocks,char figure, Color color, Point startPoint, bool isWithColors);
	Block& operator=(const Block& b);
	bool getIsEmpty()const;
	bool shouldBlockFall(const vector<vector<char>>& boardGame)const;
};