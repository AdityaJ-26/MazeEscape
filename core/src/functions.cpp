#include <random>
#include "..\include\functions.h"
#include "..\include\constants.h"

void init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "_lib_error : error occured while initialising library" << std::endl;
		exit(-1);
	}
}

bool inBound(int32_t x, int32_t y) {
	return ((x >= 0 && x < MAZE_SIZE) && (y >= 0 && y < MAZE_SIZE));
}