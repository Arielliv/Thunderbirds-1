#pragma once

#include "color.h"
#include "point.h"
#include "constants.h"
#include "boardUtils.h"
#include "Block.h"
#include <vector>


enum class ShipSize{ Small = 2, Big=4 };

class Ship
{
	ShipSize shipSize;
	Point startPoint = Point(1,1);
	char figure;
	Color color;
	Direction direction = Direction::Right;
	vector<Point> body;
	bool isWithColors = false;
	bool isEmpty = true;
private:
	bool isSmallShipNextMoveEQCellType(const BoardCellType cellType, const vector<vector<char>>& boardGame) const;
	bool isBigShipNextMoveEQCellType(const BoardCellType cellType, const vector<vector<char>>& boardGame) const;
	bool isBigShipValidBlockMove(BoardCellType* blockType, const vector<vector<char>>& boardGame) const;
	bool isSmallShipValidMoveBlock(const vector<vector<char>>& boardGame) const;
public:
	Ship();
	Ship(ShipSize shipSize, char figure, Color color, Point startPoint, bool isWithColors);
	void setDirection(const Direction _direction);
	Direction getDirection() const;
	Point getCurrentShipPoint() const;
	const vector<Point> getCurrentBodyPoints() const;
	void move(vector<vector<char>>& boardGame);
	void draw(vector<vector<char>>& boardGame) const;
	void erase(vector<vector<char>>& boardGame) const;
	Ship& operator=(const Ship& s);
	bool isShipEmpty();
	~Ship();


	bool isNextMoveEQCellType(const BoardCellType cellType, const vector<vector<char>>& boardGame) const;
	bool isShipValidBlockMove(BoardCellType* blockType, const vector<vector<char>>& boardGame) const;
	bool shouldShipBeExploed(const vector<vector<char>>& boardGame, const Block bigBlock) const;
};
