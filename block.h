#pragma once

#include "color.h"
#include "point.h"
#include "constants.h"
#include "boardUtils.h"
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

private:
	bool isBigBlockValidMove(const Direction dir, const vector<vector<char>>& boardGame) const;
	bool isSmallBlockValidMove(const Direction dir, const vector<vector<char>>& boardGame) const;
public:
	Block(BlockSize blockSize, char figure, Color color, Point startPoint, bool isWithColors);
	Block& operator=(const Block& b);
	Point getCurrentBlockPoint() const;
	const vector<Point> getCurrentBodyPoints() const;
	void move(const Direction direction, vector<vector<char>>& boardGame);
	void draw(vector<vector<char>>& boardGame) const;
	~Block();

	bool isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const;
};