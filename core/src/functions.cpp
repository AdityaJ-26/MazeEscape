#include <random>
#include "..\include\functions.h"

void init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "_lib_error : error occured while initialising library" << std::endl;
		exit(-1);
	}
}