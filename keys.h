#pragma once

#include "point.h"
#include "utils.h"

enum { ESC = 27 };

enum class Keys
{
	Up, 
	Down,
	Left,
	Right,
	SwitchSmall,
	SwitchBig
};

Direction getDirectionByKey(char key);
