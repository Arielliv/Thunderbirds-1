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
#include "gameFile.h"
#include <typeinfo>

class Board{
	Ship bigShip;
	Ship smallShip;
	vector<Block> blocks;
	vector<shared_ptr<Ghost>> ghosts;
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
	bool isSaveMode;
	bool isFileMode;
	GameFile stepsFile;
	GameFile resultFile;
	std::string screenNumber;
private:
	bool smallShipMove();
	bool bigShipMove();

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

	bool isInFileSaveMode() const;
	bool isInFilLoadMode() const;
public:
	Board() {};
	Board(bool isWithColors, int time, BoardCellType controlledShip, string _boardGame, int legendLocation, int numOfBlocks, int numOfGhosts, std::string screenNumber,bool isFileMode = false,bool isSaveMode = false);
	bool play(bool& isEsc, const int lives);
	~Board();
};

