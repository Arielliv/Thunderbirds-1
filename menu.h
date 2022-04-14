#pragma once
#include <iostream>
#include <string>
#include "ioUtils.h"
#include "point.h"

enum class MenuChoice {WithColor = 1, WithoutColor = 2, Exit = 3, ShowSettings = 4, OpenFileByName = 5};

class Menu
{
private:
	void printMenu() const;
	void printInstructions() const;
	void printSettings() const;
	bool openSettings() const;
public:
	MenuChoice openMenu() const;
};

