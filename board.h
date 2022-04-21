#pragma once
#include <string>
#include "ship.h"
#include "keys.h"
#include "point.h"
#include "block.h"
#include <vector>
#include "ghost.h"
#include "constants.h"

class Board{
	Ship bigShip;
	Ship smallShip;
	vector<Block> blocks;
	vector<Ghost> ghosts;
	bool isWithColors = false;
	bool isVictory = false;
	bool isLoss = false;
	vector<bool> exitsStatus = { false,false };
	bool isSmallShipMove = false;
	vector<vector<char>> boardGame;
	int time = 500;
	int numOfBlocks;
	int legendLocation;
private:
	void smallShipMove();
	void bigShipMove();

	bool isSmallShipValidMove() const;
	bool isBigShipValidMove() const;
	bool isSmallShipVictoryMove() const;
	bool isBigShipVictoryMove() const;
	bool shouldShipBeExploed() const;

	void updateExitsStatus(const ShipSize shipSize);

	void initBoard();

	void printStatus(const int lives) const;
	void printTimer() const;
	void printShipTurn() const;
	void printRemainingLives(const int lives) const;
	void printEscOptions() const;
	void printBoard() const;

	void updateValueByCellType(const BoardCellType cellType, const bool shouldErase);
	bool runTheGame(const int lives);
	bool isShipValidMove(const ShipSize shipSize) const;
	vector<int> getFallingBlockIndexes() const;
	void dropBlocks(const vector<int> blockIndexes);
	void updateVictory();

	void moveGhosts();
public:
	//Board(bool isWithColors = false);
	Board() {};
	Board& operator=(const Board& b);
	Board(bool isWithColors, int time, BoardCellType controlledShip, string _boardGame, int legendLocation, int numOfBlocks);
	bool play(bool& isEsc, const int lives);
	friend void clearLine(const int lineNumber);
	~Board();
};

