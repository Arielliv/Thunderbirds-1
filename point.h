#pragma once


#include <iostream>
#include "ioUtils.h"

using namespace std;

class point {
	int x = 1, y = 1;
public:
	void draw(char ch);
	//void move();
	void move(int direction);
};



