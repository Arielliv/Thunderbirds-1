#pragma once
#include <cctype>
#include "point.h"
#include "utils.h"

enum { ESC = 27 };

enum class Keys
{
	Up=0, 
	Down=1,
	Left=2,
	Right=3,
	SwitchSmall=4,
	SwitchBig=5,
	None=6
};

Direction getDirectionByKey(char key);
Keys getKeyByChar(char key);
