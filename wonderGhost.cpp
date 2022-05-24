#include "wonderGhost.h"

WonderGhost::WonderGhost(char figure, Color color, Point startPoint, bool isWithColors, const vector<vector<char>>& boardGame) : Ghost(figure, color, startPoint, isWithColors, GhostType::Wondering) {
	this->generateNextDirection(boardGame);
};

void WonderGhost::generateNextDirection(const vector<vector<char>>& boardGame) {
	this->setDirection((Direction)getRandomNum(0, 3));
}

bool WonderGhost::isValidMoveAuto(const vector<vector<char>>& boardGame) {
	this->generateNextDirection(boardGame);
	return Ghost::isValidMoveAuto(boardGame);
}