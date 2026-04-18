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
	double start = SDL_GetTicks();

	while (game->running == true) {

		double deltaTime = SDL_GetTicks() - start;
		start = SDL_GetTicks();
		game->input();

		game->update(deltaTime/1000);
		if (deltaTime < frameTime) {
			SDL_Delay(frameTime - deltaTime);
		}

		game->render();
		game->render(1);
		system("cls");
	}

	delete game;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();

	return 0;
}
