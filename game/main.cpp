#include <iostream>

#include "game.h"
#include "maze.h"
#include "constants.h"

#include "assets.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game();

	while (game->running == true) {

		game->handleEvents();
		game->render();
		game->update();
		system("cls");
	}
	return 0;
}