#include <iostream>

#include "SDL.h"
#include "SDL_image.h"

#include "functions.h"
#include "GameObject.h"

constexpr int frameCap = 60;
constexpr float frameTime = 1000.0 / frameCap;
constexpr float animationTime = 100.0f;

// Global variables
Game* game = nullptr;
SDL_Window* window = nullptr;
GameMenu* gameMenu = nullptr;

int main(int argc, char* argv[])
{

	// Initialisations of game elements
	init();
	window = window_init();
	gameMenu = new GameMenu();
	game = new Game(window);
	SDL_Renderer* renderer = game->getRenderer();
	gameMenu->load(renderer);

	// loading menu at start
	game->render(0);
	game->running = menuWindow(gameMenu, renderer);

	// frame element intialisation
	unsigned char currFrame = 0;
	float start = SDL_GetTicks();
	float frameSpeed = 0.0f;


	// game loop
	while (game->running == true) {

		double deltaTime = SDL_GetTicks() - start;
		start = SDL_GetTicks();

		//input handling
		game->input();

		// animation updation after certain ticks
		frameSpeed += deltaTime;
		if (frameSpeed >= animationTime) {
			frameSpeed -= animationTime;
			currFrame = (currFrame + 1) % 8;
		}
		
		// update method requires deltaTime
		game->update(deltaTime/1000.0, currFrame);

		// delaying to maintain 60FPS
		if (deltaTime < frameTime) {
			SDL_Delay(frameTime - deltaTime);
		}

		game->render(currFrame);
	}

	// game ending screen
	if (game->won) {
		gameWinWindow(gameMenu, game->getRenderer());
	}
	else {
		gameOverWindow(gameMenu, game->getRenderer());
	}

	// memory freeing
	quit(game, window);

	return 0;
}
