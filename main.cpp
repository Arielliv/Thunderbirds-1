#include "game.h"
#include "utils.h"
//argv [load/save,silent]
int main(int argc, char* argv[]) {
	string mode;
	bool isLoadMode = false;
	bool isSaveMode = false;
	bool isSilnet = false;

	if (argc > 1) {
		mode = argv[1];
		if (mode.compare("-Load") == 0) {
			isLoadMode = true;
		}
		if (mode.compare("-Save") == 0){
			isSaveMode = true;
		}
		if (argc > 2 && isLoadMode) {
			isSilnet = true;
		}
	}
	Game game;
	initRandomize();
	game.start(isLoadMode, isSaveMode, isSilnet);
}