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
	bool isWithColors = false;
	bool isVictory = false;
	bool isLoss = false;
	bool exitsStatus[2] = { false,false };
	bool isSmallShipMove = false;
	int time = 500;
private:
	void setValueByIndex(const Point p, const BoardCellType boardCellType);
	
	void smallShipMove();
	void bigShipMove();
	bool isSmallShipValidMove() const;
	bool isBigShipValidMove() const;
	bool shouldShipBeExploed() const;
	bool isShipValidMove(const ShipSize shipSize) const;

	void smallBlockMove(const Direction dir);
	void bigBlockMove(const Direction dir);
	bool isSmallBlockValidMove(const Direction dir) const;
	bool isBigBlockValidMove(const Direction dir) const;
	bool isBlockValidMove(const BlockSize blockSize, const Direction dir) const;
	void getFallingBlockTypes(BlockSize* results) const;
	void dropBlocks(const BlockSize(&fallingBlocks)[2]);

	bool isSmallShipValidMoveBlock() const;
	bool isBigShipValidBlockMove(BoardCellType* blockType) const;

	void updateExitsStatus(const ShipSize shipSize);

	bool isSmallShipVictoryMove() const;
	bool isBigShipVictoryMove() const;
	//bool isBigShipNextMoveEQCellType(const BoardCellType cellType) const;
	bool isSmallShipNextMoveEQCellType(const BoardCellType cellType) const;

	void initBoard();
	void updateValueByPoints(const Point* points, const int size, const BoardCellType cellType);

	void printStatus(const int lives) const;
	void printTimer() const;
	void printShipTurn() const;
	void printRemainingLives(const int lives) const;
	void printEscOptions() const;
	void printBoard() const;

	void updateValueByCellType(const BoardCellType cellType, const bool shouldErase);
	bool runTheGame(const int lives);
	void updateVictory();
public:
	char boardGame[Bounderies::rows][Bounderies::cols];

	Board(bool isWithColors = false);
	Board& operator=(const Board& b);
	bool play(bool* isEsc, const int lives);
	friend void clearLine(const int lineNumber);
	//friend BoardCellType getValueByIndex(const Point p, const char (&boardGame)[Bounderies::rows][Bounderies::cols]);
};

