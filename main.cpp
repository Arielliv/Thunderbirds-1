#include "game.h"
#include "utils.h"
//argv [load/save,silent]
int main(int argc, char* argv[]) {
	string mode, option;
	bool isLoadMode = false;
	bool isSaveMode = false;
	bool isWithColors = false;
	bool isSilnet = false;

	if (argc > 1) {
		mode = argv[1];
		if (mode.compare("-Load") == 0) {
			isLoadMode = true;
		}
		if (mode.compare("-Save") == 0){
			isSaveMode = true;
		}
		if (argc > 2) {
			option = argv[2];
			if (isLoadMode && option.compare("-Silent") == 0) {
				isSilnet = true;
			}
			if (isLoadMode && option.compare("-Color") == 0) {
				isWithColors = true;
			}
		}
	}
	Game game;
	initRandomize();
	game.start(isLoadMode, isSaveMode, isSilnet, isWithColors);
}