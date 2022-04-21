#pragma once
#include <iostream>
#include <string>
#include "ioUtils.h"
#include "point.h"

enum class MenuChoice {WithColor = 1, WithoutColor = 2, Exit = 3, ShowSettings = 4, OpenFileByNameWithColor = 5, OpenFileByNameWithoutColor = 6};

class Menu
{
private:
	void printMenu() const;
	void printInstructions() const;
	void printSettings() const;
	bool openSettings() const;
public:
	MenuChoice openMenu() const;
	void printExit() const;
	void printWin() const;
	void printLoss() const;
	std::string getFileName() const;
};

