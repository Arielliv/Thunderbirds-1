#pragma once
#include <cctype>
#include "point.h"
#include "utils.h"

enum { ESC = 27, ESC_SECOND = '9' };

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

Direction getDirectionByKey(const char key);
Keys getKeyByChar(const char key);
