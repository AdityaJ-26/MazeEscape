#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "functions.h"
#include "GameObject.h"

Game* game = nullptr;
SDL_Window* window = nullptr;

int main(int argc, char* argv[])
{

	init();
	window = window_init();
	game = new Game(window);
	int frame = 60;
	double frameTime = 1000.0 / frame;
	double botDelay = 1000.0 / 24;
	double botStart = SDL_GetTicks();
	unsigned char currFrame = 0;

	while (game->running == true) {

		double start = SDL_GetTicks();

		game->input();
		game->render();

		double time = SDL_GetTicks();
		if (time - botStart > botDelay) {
			currFrame = (currFrame + 1) % 8;
			botStart = time;
			game->update(currFrame);
		}

		double deltaTime = time - start;
		if (deltaTime < frameTime) {
			SDL_Delay(frameTime - deltaTime);
		}
	}

	delete game;

	return 0;
}
