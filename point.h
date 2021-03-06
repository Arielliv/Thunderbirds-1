#pragma once

#include "constants.h"
#include <iostream>
#include "ioUtils.h"

using namespace std;

enum class Direction { Up = 0, Down = 1, Left = 2, Right = 3, None=4};

class Point {
	int x = 1, y = 1;
public:
	Point() :x(1), y(1) {}
	Point(int x,int y):x(x), y(y){}
	void draw(char ch) const;
	void move(const Direction direction);
	int getXPoint() const;
	int getYPoint() const;
	~Point();
	bool operator==(const Point& p) const;
	Point& operator=(const Point& p);
};



