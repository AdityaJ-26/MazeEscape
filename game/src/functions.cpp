#include <iostream>

#include "functions.h"

void init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "_lib_error : " << SDL_GetError() << std::endl;
		exit(-1);
	}
	else {
		if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
			std::cerr << "_lib_error : " << IMG_GetError() << std::endl;
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
	return window;
}


bool menuWindow(GameMenu* gameMenu, SDL_Renderer* renderer) {
	SDL_Event e;
	while (true) {
		SDL_RenderClear(renderer);
		gameMenu->renderMenu(renderer);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_RETURN) {
					return true;
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
}

void gameOverWindow(GameMenu* gameMenu, SDL_Renderer* renderer) {
	SDL_Event e;
	while (true) {
		SDL_RenderClear(renderer);
		gameMenu->renderOver(renderer);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_RETURN) {
					return;
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
}

void gameWinWindow(GameMenu* gameMenu, SDL_Renderer* renderer) {
	SDL_Event e;
	while (true) {
		SDL_RenderClear(renderer);
		gameMenu->renderWin(renderer);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_RETURN) {
					return;
				}
			}
		}
		SDL_RenderPresent(renderer);
	}
}

void quit(Game* game, SDL_Window* window) {
	delete game;
	game = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
}