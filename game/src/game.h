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
		Player* user;
		App* app;
		Texture* textures;

	private:
		void spawnKeys();
		void processPlayer();
		bool isMovable(int32_t, int32_t) const;

	public:
		bool running;
	
	public:
		Game();
		void handleEvents();
		void render();
		void render(int);
		void update();
		~Game();
};

#endif // !GAME_H
