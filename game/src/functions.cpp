#include <iostream>

#include "functions.h"

void init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "_lib_error : " << SDL_GetError() << std::endl;
		exit(-1);
	}
	else {
		if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
			std::cerr << "_lib_error : " << SDL_GetError() << std::endl;
			exit(-1);
		}
	}
}


SDL_Window* window_init() {
	SDL_Window* window = SDL_CreateWindow(
		TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);
	if (window == nullptr) {
		std::cerr << "_window_error : " << SDL_GetError() << std::endl;
		exit(-1);
	}
}