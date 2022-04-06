#include "block.h"

Block& Block::operator=(const Block& b) {
	this->blockSize = b.blockSize;
	this->startPoint = b.startPoint;
	this->figure = b.figure;
	this->color = b.color;
	this->isWithColors = b.isWithColors;
	
	for (Point p : b.body) {
		body.push_back(p);
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

void Block::move(const Direction direction) {
	
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
}


void Block::draw() const {
	for (std::size_t i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(figure);
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	}
}

Block::~Block() {
	
}

Point Block::getCurrentBlockPoint() const{
	return Point(this->body[0]);
}

const vector<Point> Block::getCurrentBodyPoints() const {
	return this->body;
}



