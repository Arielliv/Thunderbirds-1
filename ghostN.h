#pragma once
#pragma once
#include "point.h"
#include "boardUtils.h"
#include "boardGameTool.h"
#include <vector>

enum class GhostType { Vertical = 1, Horizontal = 2, Wondering = 3 };

class AbstractGhost: public BoardGameTool {
	GhostType type;
	Direction direction;
public:
	AbstractGhost(char figure, Color color, Point startPoint, bool isWithColors, GhostType type, Direction direction) : BoardGameTool(figure, color, startPoint, isWithColors), type(type), direction(direction) {};
	virtual bool isValidMove(const Direction dir, const vector<vector<char>>& boardGame) const override;
	virtual bool isHitShip(const vector<vector<char>>& boardGame) const;
	Direction getDirection() const;
	GhostType getGhostType() const;
};

