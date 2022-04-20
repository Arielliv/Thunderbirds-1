#pragma once
#include <iostream>
#include <vector>
#include "point.h"
#include "constants.h"

char getValueByIndex(const Point p, const vector<vector<char>>& boardGame);
void updateValueByPoints(const vector<Point> points, const int size, const char cellType, vector<vector<char>>& boardGame);
void setValueByIndex(const Point p, const char boardCellType, vector<vector<char>>& boardGame);