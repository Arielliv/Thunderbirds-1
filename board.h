#pragma once
#include <string>
#include "ship.h"
#include "keys.h"
#include "point.h"
#include "block.h"

enum class BoardCellType {
	Empty = '0',
	Wall = '1',
	SmallShip = '2',
	BigShip = '3',
	SmallBlock = '4',
	BigBlock = '5',
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
	void smallShipMove();
	void bigShipMove();

	bool isSmallShipValidMove();
	bool isBigShipValidMove();

	bool isSmallBlockValidMove(Direction dir);
	bool isBigBlockValidMove(Direction dir);

	bool isSmallShipNextToBlock();
	bool isBigShipNextToBlock(BoardCellType* blockType);
public:
	Board();
	BoardCellType getValueByIndex(Point p);
	void printBoard();
	void updateValueByPoints(Point* points, int size, BoardCellType cellType);
	bool isShipValidMove(ShipSize shipSize);
	bool isBlockValidMove(BlockSize blockSize, Direction dir);
	void start();
};