#ifndef GAME_H
#define GAME_H

#include <vector>

#include "core.h"
#include "render.h"



class Game {

	// private members
	private:
		Maze maze;
		std::vector<Key*> keys;
		std::vector<Bot*> bots;
		Player* user;
		App* app;
		Texture* textures;
	
	// public members
	public:
		bool running;

	// private functions
	private:
		void spawnKeys();
		void spawnBots();
		void processPlayer();
		bool isMovable(int32_t, int32_t) const;
		const int32_t& distance(const int32_t&, const int32_t&, const int32_t&, const int32_t&);
		const int32_t& distance(const Coordinate&, const Coordinate&);
		void collisionCheck(const Bot*);
		void gameOver();
		void processBots(int);
	
	// public functions
	public:
		Game();
		void handleEvents();
		void render();
		void render(int);
		void update(int);
		~Game();
};

#endif // !GAME_H
