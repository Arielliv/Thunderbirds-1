#include "game.h"
#include "utils.h"
//argv [load/save,silent]
int main(int argc, char* argv[]) {
	Game game;
	string mode, option;
	bool isLoadMode = false;
	bool isSaveMode = false;
	bool isWithColors = false;
	bool isSilnet = false;

	if (argc > 1) {
		mode = argv[1];
		if (mode.compare("-load") == 0) {
			isLoadMode = true;
		}
		if (mode.compare("-save") == 0){
			isSaveMode = true;
		}
		if (argc > 2 && isLoadMode) {
			option = argv[2];
			if (isLoadMode && option.compare("-silent") == 0) {
				isSilnet = true;
			}
			if (isLoadMode && option.compare("-color") == 0) {
				isWithColors = true;
			}
		}
	}

	initRandomize();
	game.start(isLoadMode, isSaveMode, isSilnet, isWithColors);
}