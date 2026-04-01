#include <iostream>

#include "game.h"
#include "render.h"

#include "SDL.h"
#include "SDL_image.h"

void init();

Game* game = nullptr;

int main(int argc, char* argv[]) {

	init();
	game = new Game();

	while (game->running == true) {

		game->handleEvents();
		game->render();
		game->render(1);
		game->update();
		system("cls");
	}
	return 0;
}

void init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "_error_SDL2_lib : " << SDL_GetError() << std::endl;
		exit(-1);
	}
	else {
		if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			std::cerr << "_error_image_lib : " << SDL_GetError() << std::endl;
			exit(-1);
		}
	}
}