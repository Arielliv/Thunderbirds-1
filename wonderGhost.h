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
	Direction prevDirection = Direction::None;
	void generateNextDirection(const vector<vector<char>>& boardGame);
public:
	WonderGhost(char figure, Color color, Point startPoint, bool isWithColors, const vector<vector<char>>& boardGame);
	bool isValidMoveAuto(const vector<vector<char>>& boardGame) override;
	bool shouldSaveToFile() const override;
};

