#include <iostream>
#include <SDL.h>

#include "include/maze.h"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Not Working" << std::endl;
		exit(-1);
	}

	Maze* maze = new Maze(29);

	std::cout << std::endl;

	maze->print();

	return 0;
}