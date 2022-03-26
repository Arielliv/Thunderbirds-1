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
	Exit = '4',
	SmallBlock = '5',
	BigBlock = '6',
};

enum Bounderies {
	rows = 23,
	cols = 80
};

class Board{
	Ship bigShip;
	Ship smallShip;
	Block bigBlock;
	Block smallBlock;
	bool isVictory = false;
	bool isLoss = false;
	bool exitsStatus[2] = { false,false };
	bool isSmallShipMove = false;
	char boardGame[Bounderies::rows][Bounderies::cols];
	int time = 500;
private:
	void setValueByIndex(Point p, BoardCellType boardCellType);
	void smallShipMove();
	void bigShipMove();
	void smallBlockMove(Direction dir);
	void bigBlockMove(Direction dir);

	bool isSmallShipValidMove();
	bool isBigShipValidMove();
	bool isSmallShipVictoryMove();
	bool isBigShipVictoryMove();
	bool shouldShipBeExploed();

	bool isSmallBlockValidMove(Direction dir);
	bool isBigBlockValidMove(Direction dir);

	bool isSmallShipNextToBlock();
	bool isBigShipNextToBlock(BoardCellType* blockType);

	void updateExitsStatus(ShipSize shipSize);

	bool isBigShipNextMoveEQCellType(BoardCellType cellType);
	bool isSmallShipNextMoveEQCellType(BoardCellType cellType);

	void initBoard();
	void updateValueByPoints(const Point* points, int size, BoardCellType cellType);
public:
	Board();
	Board& operator=(const Board& b);
	BoardCellType getValueByIndex(Point p);
	void printBoard();
	void printStatus(int lives);
	void printTimer();
	void printShipTurn();
	void printRemainingLives(int lives);
	void updateValueByCellType(BoardCellType cellType, bool shouldErase);
	bool isShipValidMove(ShipSize shipSize);
	bool isBlockValidMove(BlockSize blockSize, Direction dir);
	void getFallingBlockTypes(BlockSize* results);
	void dropBlocks(const BlockSize(&fallingBlocks)[2]);
	void updateVictory();
	bool runTheGame(int lives);
	bool play(bool* isEsc, int lives);
	friend void clearLine(int lineNumber);
};

