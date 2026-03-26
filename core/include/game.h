#ifndef GAME_H
#define GAME_H

#include <vector>
#include "coordinate.h"
#include "maze.h"
#include "key.h"
//#include "bots.h"
#include "player.h"

class Game {
	private:
		Maze maze;
		std::vector<Key*> keys;
		//std::vector<Bots*> bots;
	private:
		void spawnKeys();
		bool inBound(int32_t, int32_t) const;
		void processPlayer();

	public:
		Player* user;
		bool running;
	
	public:
		Game();
		void handleEvents();
		void print();
		void update();
};

#endif // !GAME_H
