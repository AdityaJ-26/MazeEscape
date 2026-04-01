#include <iostream>

#include "app.h"

App::App() :
	window(nullptr),
	renderer(nullptr)
{ }

App::~App() {
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
}

void App::App_Init() {
	window = SDL_CreateWindow(
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
	else {
		renderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_ACCELERATED
		);
		if (renderer == nullptr) {
			std::cerr << "_renderer_error : " << SDL_GetError() << std::endl;
			exit(-1);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
}

void App::render(SDL_Texture* texture, SDL_Rect* rect) const {
	SDL_RenderCopy(renderer, texture, nullptr, rect);
}