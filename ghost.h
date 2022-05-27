#pragma once
#pragma once
#include "point.h"
#include "boardUtils.h"
#include "boardGameTool.h"
#include <vector>

enum class GhostType { Vertical = 1, Horizontal = 2, Wondering = 3 };

class Ghost : public BoardGameTool {
	GhostType type;
	Direction direction;
public:	
	Ghost() {};
	Ghost(char figure, Color color, Point startPoint, bool isWithColors, GhostType type, bool isSilent, Direction direction = Direction::None) : BoardGameTool(figure, color, startPoint, isWithColors, isSilent), type(type), direction(direction) {
		this->pushToBody(Point(startPoint.getYPoint(), startPoint.getXPoint()));
	};
	virtual bool isValidMoveAuto(const vector<vector<char>>& boardGame);
	virtual bool isHitShip(const vector<vector<char>>& boardGame);
	Direction getDirection() const;
	void setDirection(Direction direction) ;
	GhostType getGhostType() const;
	virtual void moveAuto(vector<vector<char>>& boardGame);
	virtual Ghost& operator=(const Ghost& b);
	virtual bool shouldSaveToFile() const;
	GhostType getType() const;
};

