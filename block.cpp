#include "block.h"

Block& Block::operator=(const Block& b) {
	this->blockSize = b.blockSize;
	this->startPoint = b.startPoint;
	this->figure = b.figure;
	this->color = b.color;
	this->isWithColors = b.isWithColors;
	
	for (int i = 0; i < (int)b.blockSize; i++) {
		body[i] = b.body[i];
	}
	return *this;
}

Block::Block(BlockSize blockSize, char figure, Color color, Point startPoint, bool isWithColors) : blockSize(blockSize), figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
	if (blockSize == BlockSize::Small) {
		this->body = new Point [(int)BlockSize::Small];
		for (int i = 0; i < 2; i++) {
			this->body[i] = Point(this->startPoint.getXPoint() + i, this->startPoint.getYPoint());
		}
	}
	else {
		this->body = new Point [(int)BlockSize::Big];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++)
			{
				this->body[i * 2 + j] = Point(this->startPoint.getXPoint() + j, this->startPoint.getYPoint() + i);
			}
		}
	}
}

void Block::move(Direction direction) {
	if (this->blockSize == BlockSize::Small) {
			for (int i = 0; i < 2; i++) {
				this->body[i].draw(' ');
				this->body[i].move(direction);
			}
			for (int i = 0; i < 2; i++) {
				if (this->isWithColors) {
					setTextColor(color);
				}
				this->body[i].draw(figure);
			}

	}
	else {
		for (int i = 0; i < 6; i++)
		{
			this->body[i].draw(' ');
			this->body[i].move(direction);
		}

		for (int i = 0; i < 6; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
		}
	}
}


void Block::draw() {
	if (this->blockSize == BlockSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
	}
	else {
		for (int i = 0; i < 6; i++)
		{
			if (this->isWithColors) {
				setTextColor(color);
			}
			this->body[i].draw(figure);
			if (this->isWithColors) {
				setTextColor(Color::WHITE);
			}
		}
	}
}

Block::~Block() {
	delete this->body;
}

Point Block::getCurrentBlockPoint() {
	return Point(this->body[0]);
}

const Point* Block::getCurrentBodyPoints() const {
	return this->body;
}



