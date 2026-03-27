#ifndef GAME_H
#define GAME_H

#include <vector>

#include "core.h"
#include "render.h"


class Game {
	private:
		Maze maze;
		std::vector<Key*> keys;
		//std::vector<Bots*> bots;
		Surfaces* surfaces;
		SDL_Window* window;

	private:
		void spawnKeys();
		bool inBound(int32_t, int32_t) const;
		void processPlayer();
		bool isMovable(int32_t, int32_t) const;

	public:
		Player* user;
		bool running;
	
	public:
		Game();
		void handleEvents();
		void render();
		void update();
		void init();
};

#endif // !GAME_H
