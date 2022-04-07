#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "constants.h"

BoardCellType getValueByIndex(const Point p, const vector<vector<char>>& boardGame);
void updateValueByPoints(const vector<Point> points, const int size, const BoardCellType cellType, vector<vector<char>>& boardGame);
void setValueByIndex(const Point p, const BoardCellType boardCellType, vector<vector<char>>& boardGame);