#pragma once
#include "point.h"
#include "boardUtils.h"
#include <vector>

enum class GhostType { Vertical = 1, Horizontal = 2, Wondering=3 };

class Ghost
{
	GhostType type;
	Direction direction;
	Point startPoint = Point(1, 1);
	char figure;
	Color color;
	Point body;
	bool isWithColors = false;
public:
	Ghost(char figure, Color color, Point startPoint, bool isWithColors, GhostType type, Direction direction);
	Ghost& operator=(const Ghost& b);
	Point getCurrentGhostPoint() const;
	void move(vector<vector<char>>& boardGame);
	void draw(vector<vector<char>>& boardGame) const;
	bool isValidMove(const vector<vector<char>>& boardGame) const;
	bool isHitShip(const vector<vector<char>>& boardGame) const;
	void setDirection(const Direction _direction);
	Direction getDirection() const;
	GhostType getGhostType() const;
};

