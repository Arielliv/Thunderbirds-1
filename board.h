#pragma once
#include <string>
#include "ship.h"
#include "keys.h"
#include "point.h"

enum class BoardCellType {
	Empty = '0',
	Wall = '1',
	Block = '2',
	SmallShip = '3',
	BigShip = '4',
};

enum Bounderies {
	rows = 25,
	cols = 80
};

class Board{
	Ship bigShip;
	Ship smallShip;
	char boardGame[Bounderies::rows][Bounderies::cols];
private:
	void setValueByIndex(Point p, BoardCellType boardCellType);
public:
	Board();
	BoardCellType getValueByIndex(Point p);
	void printBoard();
	void updateValueByPoints(Point* points, int size, BoardCellType cellType);
	bool isValidMove(ShipSize shipSize);
	void start();
};