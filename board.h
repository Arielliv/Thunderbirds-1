#pragma once
#include <string>
#include "ship.h"
#include "keys.h"
#include "point.h"
#include "block.h"
#include <vector>
#include "ghost.h"
#include "constants.h"
#include "boardUtils.h"
#include "legened.h"
#include "wonderGhost.h"

class Board{
	Ship bigShip;
	Ship smallShip;
	vector<Block> blocks;
	vector<Ghost*> ghosts;
	bool isWithColors = false;
	bool isVictory = false;
	bool isLoss = false;
	vector<bool> exitsStatus = { false,false };
	bool isSmallShipMove = false;
	vector<vector<char>> boardGame;
	int time = 500;
	int numOfBlocks;
	int numOfGhosts;
	Legened legened;
private:
	void smallShipMove();
	void bigShipMove();

	bool shouldShipBeExploed() const;

	void updateExitsStatus(const ShipSize shipSize);

	void initBoard();

	void printBoard() const;

	void updateValueByCellType(const BoardCellType cellType, const bool shouldErase);
	bool runTheGame(const int lives);
	const vector<int> getFallingBlockIndexes() const;
	void dropBlocks(const vector<int> blockIndexes);
	void updateVictory();

	void moveGhosts();
public:
	Board() {};
	Board(bool isWithColors, int time, BoardCellType controlledShip, string _boardGame, int legendLocation, int numOfBlocks, int numOfGhosts);
	bool play(bool& isEsc, const int lives);
	~Board();
};

