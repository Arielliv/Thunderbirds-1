#include "boardGameTool.h"

BoardGameTool& BoardGameTool::operator=(const BoardGameTool& b) {
	this->startPoint = b.startPoint;
	this->figure = b.figure;
	this->color = b.color;
	this->isWithColors = b.isWithColors;
	this->body = b.body;
	return *this;
}

BoardGameTool::BoardGameTool(char figure, Color color, Point startPoint, bool isWithColors) : figure(figure), color(color), startPoint(startPoint), isWithColors(isWithColors) {
}

void BoardGameTool::move(const Direction direction, vector<vector<char>>& boardGame) {
	updateValueByPoints(this->body, this->body.size(), (char)BoardCellType::Empty, boardGame);
	for (int i = 0; i < this->body.size(); i++) {

		this->body[i].draw(' ');
		this->body[i].move(direction);
	}
	for (int i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(figure);
	}
	updateValueByPoints(this->body, this->body.size(), this->figure, boardGame);
}


void BoardGameTool::draw(vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->body.size(); i++) {
		if (this->isWithColors) {
			setTextColor(color);
		}
		this->body[i].draw(figure);
		if (this->isWithColors) {
			setTextColor(Color::WHITE);
		}
	}

	updateValueByPoints(this->body, this->body.size(), this->figure, boardGame);
}

BoardGameTool::~BoardGameTool() {
	this->body.clear();
}

const Point& BoardGameTool::getCurrentPoint() const {
	return this->body[0];
}

const vector<Point>& BoardGameTool::getCurrentBodyPoints() const {
	return this->body;
}

bool BoardGameTool::isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const {
	for (int i = 0; i < this->body.size(); i++) {
		Point curBlockPoint = this->body[i];
		int curBlockPointY = curBlockPoint.getYPoint();
		int curBlockPointX = curBlockPoint.getXPoint();

		switch (dir) {
		case Direction::Up:
			if (getValueByIndex(Point(curBlockPointY - 1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY - 1, curBlockPointX), boardGame) != this->figure) {
				return false;
			}
			break;
		case Direction::Down:
			if (getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY + 1, curBlockPointX), boardGame) != this->figure) {
				return false;
			}

			break;
		case Direction::Left:
			if (getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY, curBlockPointX - 1), boardGame) != this->figure) {
				return false;
			}

			break;
		case Direction::Right:
			if (getValueByIndex(Point(curBlockPointY, curBlockPointX + 1), boardGame) != (char)BoardCellType::Empty &&
				getValueByIndex(Point(curBlockPointY, curBlockPointX + 1), boardGame) != this->figure) {
				return false;
			}

			break;
		}
	}
	return true;
}

int BoardGameTool::getSize() const {
	return this->body.size();
}
char BoardGameTool::getFigure()const {
	return this->figure;
}

void BoardGameTool::pushToBody(Point p) {
	this->body.push_back(p);
}

const vector<Point>& BoardGameTool::getBody() const{
	return this->body;
}

bool BoardGameTool::getIsWithColors() const {
	return this->isWithColors;
}

Color BoardGameTool::getColor() const {
	return this->color;
}

Point BoardGameTool::getStartPoint() const {
	return this->startPoint;
}

void BoardGameTool::setBodyAt(Point p, int index) {
	this->body[index] = p;
}