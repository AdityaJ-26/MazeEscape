#include <iostream>
#include <SDL.h>

#include "include\game.h"
#include "include\maze.h"
#include "include\functions.h"
#include "include\constants.h"

int main(int argc, char* argv[]) {
	
	Game game;
	init();

	while (game.running == true) {
		game.handleEvents();
		game.print();
		game.update();
		SDL_Delay(16);
		system("cls");
	}


	return 0;
}