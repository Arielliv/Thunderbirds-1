#pragma once
#include <iostream>
#include "ioUtils.h"
#include <vector>
#include "point.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

int findInArray(const char arr[], const int n, const char c);
int parseCharToInt(char c);
char parseIntToChar(int i);
void initRandomize();
int getRandomNum(int min, int max);