#include "block.h"

Block::Block(BlockSize blockSize, char figure, Color color, Point startPoint) : blockSize(blockSize), figure(figure), color(color), startPoint(startPoint) {
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
				setTextColor(color);
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
			setTextColor(color);
			this->body[i].draw(figure);
		}
	}
}


void Block::draw() {
	if (this->blockSize == BlockSize::Small) {
		for (int i = 0; i < 2; i++)
		{
			setTextColor(color);
			this->body[i].draw(figure);
			setTextColor(Color::WHITE);
		}
	}
	else {
		for (int i = 0; i < 6; i++)
		{
			setTextColor(color);
			this->body[i].draw(figure);
			setTextColor(Color::WHITE);
		}
	}
}

Block::~Block() {
	delete this->body;
}

Point Block::getCurrentBlockPoint() {
	return Point(this->body[0]);
}

Point* Block::getCurrentBodyPoints() {
	Point* curPoints;
	if (this->blockSize == BlockSize::Small) {
		curPoints = new Point[2];
		for (int i = 0; i < 2; i++) {
			curPoints[i] = this->body[i];
		}
	}
	else {
		curPoints = new Point[6];
		for (int i = 0; i < 6; i++)
		{
			curPoints[i] = this->body[i];
		}
	}
	return curPoints;
}



