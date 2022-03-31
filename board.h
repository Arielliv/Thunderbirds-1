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
	char boardGame[Bounderies::rows][Bounderies::cols];
	int time = 500;
private:
	void setValueByIndex(const Point p, const BoardCellType boardCellType);
	void smallShipMove();
	void bigShipMove();
	void smallBlockMove(const Direction dir);
	void bigBlockMove(const Direction dir);

	bool isSmallShipValidMove() const;
	bool isBigShipValidMove() const;
	bool isSmallShipVictoryMove() const;
	bool isBigShipVictoryMove() const;
	bool shouldShipBeExploed() const;

	bool isSmallBlockValidMove(const Direction dir) const;
	bool isBigBlockValidMove(const Direction dir) const;

	bool isSmallShipValidMoveBlock() const;
	bool isBigShipValidBlockMove(BoardCellType* blockType) const;

	void updateExitsStatus(const ShipSize shipSize);

	bool isBigShipNextMoveEQCellType(const BoardCellType cellType) const;
	bool isSmallShipNextMoveEQCellType(const BoardCellType cellType) const;

	void initBoard();
	void updateValueByPoints(const Point* points, const int size, const BoardCellType cellType);

	void printStatus(const int lives) const;
	void printTimer() const;
	void printShipTurn() const;
	void printRemainingLives(const int lives) const;
	void printEscOptions() const;
	void printBoard() const;

	BoardCellType getValueByIndex(const Point p) const;
	void updateValueByCellType(const BoardCellType cellType, const bool shouldErase);
	bool runTheGame(const int lives);
	bool isShipValidMove(const ShipSize shipSize) const;
	bool isBlockValidMove(const BlockSize blockSize, const Direction dir) const;
	void getFallingBlockTypes(BlockSize* results) const;
	void dropBlocks(const BlockSize(&fallingBlocks)[2]);
	void updateVictory();
public:
	Board(bool isWithColors = false);
	Board& operator=(const Board& b);
	bool play(bool* isEsc, const int lives);
	friend void clearLine(const int lineNumber);
};

