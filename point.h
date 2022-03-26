#pragma once


#include <iostream>
#include "ioUtils.h"

using namespace std;

enum class Direction { Up = 0, Down = 1, Left = 2, Right = 3};

class Point {
	int x = 1, y = 1;
public:
	Point() :x(1), y(1) {}
	Point(int x,int y):x(x), y(y){}
	void draw(char ch) const;
	void move(const Direction direction);
	int getXPoint() const;
	int getYPoint() const;
};



