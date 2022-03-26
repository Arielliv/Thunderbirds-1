#include "menu.h"

MenuChoice Menu::openMenu() const {
	char input = '0';
	bool isWithColor = false;
	
	this->printMenu();

	while (input != '1' && input != '8' && input != '9') {
		if (_kbhit()) {
			input = _getch();
		}
	}

	if (input == '9') {
		return MenuChoice::Exit;
	}
	if (input == '8') {
		this->printInstructions();
		return MenuChoice::ShowSettings;
	}
	if (input == '1') {
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

void Menu::printMenu() const {
	std::string const menu =
		"--------------------------------------------------------------------------------\n"
		"       _______ _                       _           _     _         _            \n"
		"      |__   __| |                     | |         | |   (_)       | |           \n"
		"         | |  | |__  __   __ _ __    _| | ___ _ __| |__  _ _ __ __| |___        \n"
		"         | |  | '_  || | | | '_  | / _` |/ _ | '__| '_ || | '__/ _` / __|       \n"
		"         | |  | | | || |_| | | | || (_| |  __/ |  | |_)|| | | | (_| |__ |       \n"
		"         |_|  |_| |_||__,__|_| |_||__,_ ||___|_|  |_.__/|_|_| |___,_|___/       \n"
		"                           __ _  __ _ _ __ ___   ___                            \n"
		"                          / _` |/ _` | '_ ` _  |/ _ |                           \n"
		"                         | (_| | (_| | | | | | || __/                           \n"
		"                         |___, ||__,_|_| |_| |_||___|                           \n"
		"                           __/ |                                                \n"
		"                          |___/                                                 \n\n\n\n"
		"                      For starting a new game enter     1                       \n"
		"                      For instructions and keys enter   8                       \n"
		"                      For exit enter                    9                       \n\n\n\n\n"
		"--------------------------------------------------------------------------------";

	clear_screen();
	std::cout << menu << std::endl;
}

void Menu::printInstructions() const {
	char key = 0;
	std::string const instructions = 
		" ___         _               _   _                __       _  __            \n"
		"|_ _|_ _  __| |_ _ _ _  _ __| |_(_)___ _ _  ___  / _|___  | |/ /___ _  _ ___\n"
		" | || ' \\(_-<  _| '_| || / _|  _| / _ \\ ' \\(_-<  > _|_ _| | ' </ -_) || (_-<\n"
		"|___|_||_/__/\\__|_|  \\_,_\\__|\\__|_\\___/_||_/__/  \\_____|  |_|\\_\\___|\\_, /__/\n"
		"                                                                    |__/     \n"
		"What is this game about?\n"
		"------------------------\n"
		"Set in the year 2065, Thunderbirds follows the exploits of\n"
		"International Rescue, a secret organization committed to saving human life.\n"
		"Players will work together using Thunderbirds characters\n"
		"to complete rescue missionsand save the day.\n\n"
		"How to play?\n"
		"------------\n"
		"W / w: to move the ship up\n"
		"X / x: to move the ship down\n"
		"A / a: to move the ship left\n"
		"D / d: to move the ship right\n"
		"S / s: to switch to the small ship\n"
		"B / b: to switch to the big ship\n"
		"ESC  : to pause the game, then press 9 to exit or ESC to unpause\n\n"
		"(Press any key to go back to the menu)";

	clear_screen();
	std::cout << instructions << std::endl;

	while (key == 0) {
		if (_kbhit()) {
			key = _getch();
		}
	}
}

bool Menu::openSettings() const {
	char choice = 'a';
	
	this->printSettings();
	while (tolower(choice) != 'y' && tolower(choice) != 'n') {
		if (_kbhit()) {
			choice = _getch();
		}
	}

	if (tolower(choice) == 'y') {
		return true;
	}
	else {
		return false;
	}
}

void Menu::printSettings() const {
	std::string const settings =
		" _    _             _     _                       _ _ _          _           \n"
		"| |  | |           | |   | |                     | (_) |        | |          \n"
		"| |  | | ___  _   _| | __| |  _   _  ___  _   _  | |_| | _____  | |_ ___     \n"
		"| |/\\| |/ _ \\| | | | |/ _` | | | | |/ _ \\| | | | | | | |/ / _ \\ | __/ _ \\    \n"
		"\\  /\\  / (_) | |_| | | (_| | | |_| | (_) | |_| | | | |   <  __/ | || (_) |   \n"
		" \\/  \\/ \\___/ \\__,_|_|\\__,_|  \\__, |\\___/ \\__,_| |_|_|_|\\_\\___|  \\__\\___/    \n"
		"                               __/ |                                         \n"
		"                              |___/                                          \n"
		"       _                        _ _   _                 _               ___  \n"
		"      | |                      (_) | | |               | |             |__ \ \n"
		" _ __ | | __ _ _   _  __      ___| |_| |__     ___ ___ | | ___  _ __ ___  ) |\n"
		"| '_ \\| |/ _` | | | | \\ \\ /\\ / / | __| '_ \\   / __/ _ \\| |/ _ \\| '__/ __|/ / \n"
		"| |_) | | (_| | |_| |  \\ V  V /| | |_| | | | | (_| (_) | | (_) | |  \\__ \\_|  \n"
		"| .__/|_|\\__,_|\\__, |   \\_/\\_/ |_|\\__|_| |_|  \\___\\___/|_|\\___/|_|  |___(_)  \n"
		"| |             __/ |                                                        \n"
		"|_|            |___/                                                         \n"
		"                      __   __      __  _   _                                 \n"
		"                      \\ \\ / /     / / | \\ | |                                \n"
		"                       \\ V /     / /  |  \\| |                                \n"
		"                        \\ /     / /   | . ` |                                \n"
		"                        | |    / /    | |\\  |                                \n"
		"                        \\_/   /_/     \\_| \\_/                                \n";
	clear_screen();
	std::cout << settings << std::endl;
}

