#include "menu.h"

MenuChoice Menu::openMenu() const {
	int input;
	bool isWithColor = false;
	std::string const menu = "Welcome to Thunderbirds game\n"
		"For starting a new game press 1\n"
		"For instructions and keys press 8\n"
		"For exit press 9\n";

	clear_screen();
	std::cout << menu << std::endl;
	std::cin >> input;

	if (input == 9) {
		return MenuChoice::Exit;
	}
	if (input == 8) {
		this->printInstructions();
		return MenuChoice::ShowSettings;
	}
	if (input == 1) {
		isWithColor = this->openSettings();
		if (isWithColor) {
			return MenuChoice::WithColor;
		}
		else {
			return MenuChoice::WithoutColor;
		}
	}
	return MenuChoice::ShowSettings;
}

void Menu::printInstructions() const {
	char key = 0;
	std::string const instructions = "Game info: Thunderbirds game\n"
		"How to play?\n"
		"W/w: to move the ship up\n"
		"X/x: to move the ship down\n"
		"A/a: to move the ship left\n"
		"D/d: to move the ship right\n"
		"S/s: to switch to the small ship\n"
		"B/b: to switch to the big ship\n"
		"ESC: to pause the game - to exit press 9 OR ESC to unpause"
		"To go back to the menu - press any key";

	clear_screen();
	std::cout << instructions << std::endl;

	while (key == 0) {
		if (_kbhit()) {
			key = _getch();
		}
	}
}

bool Menu::openSettings() const {
	char choice;
	std::string const settings = "Would you like to play with colors? Y/N";
	clear_screen();
	std::cout << settings << std::endl;
	std::cin >> choice;

	if (tolower(choice) == 'y') {
		return true;
	}
	else {
		return false;
	}
}

