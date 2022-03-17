#pragma once


#include <iostream>
#include "ioUtils.h"

using namespace std;

/*
* directions
* 0 - up
* 1 - dwon
* 2 - left
* 3 - right
*/

enum class Direction { Up = 0, Down = 1, Left = 2, Right = 3};

class point {
	int x = 1, y = 1;
public:
	point() :x(1), y(1) {}
	point(int _x,int _y):x(_x), y(_y){}
	void draw(char ch);
	//void move();
	void move(Direction direction);
	int getXPoint();
	int getYPoint();
};



