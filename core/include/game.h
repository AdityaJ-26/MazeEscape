#ifndef GAME_H
#define GAME_H

#include <vector>
#include "coordinate.h"
#include "maze.h"
//#include "objective.h"
//#include "bots.h"
#include "player.h"

class Game {
	private:
		Maze maze;
		//std::vector<Objective*> obj;
		//std::vector<Bots*> bots;

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
