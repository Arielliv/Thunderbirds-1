#pragma once
#include <string>
#include "ship.h"
#include "keys.h"
#include "point.h"
#include "block.h"

enum class BoardCellType {
	Empty = '0',
	Wall = '1',
	SmallBlock = '2',
	BigBlock = '3',
	SmallShip = '4',
	BigShip = '5',
};

enum Bounderies {
	rows = 25,
	cols = 80
};

class Board{
	Ship bigShip;
	Ship smallShip;
	Block bigBlock;
	Block smallBlock;
	char boardGame[Bounderies::rows][Bounderies::cols];
private:
	void setValueByIndex(Point p, BoardCellType boardCellType);
	bool isSmallShipValidMove();
	bool isBigShipValidMove();
	bool isBlockNextToSmallShip();
public:
	Board();
	BoardCellType getValueByIndex(Point p);
	void printBoard();
	void updateValueByPoints(Point* points, int size, BoardCellType cellType);
	bool isValidMove(ShipSize shipSize);
	void start();
};