#include <iostream>
#include <SDL.h>

#include "include\game.h"
#include "include\maze.h"
#include "include\constants.h"


void init();


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


void init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "_lib_error : error occured while initialising library" << std::endl;
		exit(-1);
	}
}