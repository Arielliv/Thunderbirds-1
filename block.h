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

public:
	Block(BlockSize blockSize, char figure, Color color, Point startPoint);
	Block& operator=(const Block& b);
	Point getCurrentBlockPoint();
	const Point* getCurrentBodyPoints() const;
	void move(Direction direction);
	void draw();
	~Block();
};