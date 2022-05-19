#pragma once
#pragma once
#include "point.h"
#include "boardUtils.h"
#include "boardGameTool.h"
#include "utils.h"
#include "ghost.h"
#include <vector>

class WonderGhost : public Ghost {
private:
	Point nextPoint;
	Point generateNextPoint(const vector<vector<char>>& boardGame);
public:
	WonderGhost(char figure, Color color, Point startPoint, bool isWithColors) : Ghost(figure, color, startPoint, isWithColors, GhostType::Wondering) {};
	bool isValidMoveAuto(const vector<vector<char>>& boardGame) const override;
	bool isHitShip(const vector<vector<char>>& boardGame) const override;
	void moveAuto(vector<vector<char>>& boardGame) override;
};

