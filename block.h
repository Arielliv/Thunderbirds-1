#pragma once

#include "color.h"
#include "point.h"

enum class  BlockSize { Small = 2, Big = 6 };

class Block
{
	BlockSize blockSize;
	Point startPoint = Point(1, 1);
	char figure;
	Color color;
	Point* body;
	bool isWithColors = false;

public:
	Block(BlockSize blockSize, char figure, Color color, Point startPoint, bool isWithColors);
	Block& operator=(const Block& b);
	Point getCurrentBlockPoint();
	const Point* getCurrentBodyPoints() const;
	void move(Direction direction);
	void draw();
	~Block();
};