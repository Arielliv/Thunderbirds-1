#pragma once
#include <string>
#include "point.h"


enum class BoardCellType{
	empty = '0',
	wall = '1',
	block = '2',
	ship = '3',
};

enum Bounderies {
	rows = 25,
	cols = 80
};

class Board{
	char boardGame[Bounderies::rows][Bounderies::cols];
public:
	Board();
	void setValueByIndex(Point p, BoardCellType boardCellType);
	BoardCellType getValueByIndex(Point p);
	void printBoard();

};