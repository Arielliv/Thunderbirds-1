#pragma once
#include <iostream>
#include "ioUtils.h"
#include "board.h"

int findInArray(const char arr[], const int n, const char c);
BoardCellType getValueByIndex(const Point p, const char(&boardGame)[Bounderies::rows][Bounderies::cols]);
