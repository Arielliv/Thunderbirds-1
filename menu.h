#pragma once
#include <iostream>
#include <string>
#include "ioUtils.h"

enum class MenuChoice {WithColor = 1, WithoutColor = 2, Exit = 3, ShowSettings = 4};

class Menu
{
public:
	MenuChoice openMenu() const;
	void printInstructions() const;
	bool openSettings() const;
};

