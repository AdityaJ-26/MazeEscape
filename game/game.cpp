#include <iostream>
#include <random>
#include <queue>

#include "game.h"


/* -------------------------------------------------- */
// Rendering
/* -------------------------------------------------- */
void Game::render() {
	for (int32_t y{ 0 }; y < MAZE_SIZE; y++) {
		for (int32_t x{ 0 }; x < MAZE_SIZE; x++) {
			if (this->user->coord() == Coordinate{ x,y }) {
				std::cout << "[]";
				continue;
			}

			bool printed = false;
			for (const auto& key : keys) {
				if (key != nullptr &&
					key->coord() == Coordinate{ x,y }) 
				{
					std::cout << "? ";
					printed = true;
					break;
				}
			}
			if (printed) continue;

			for (const auto& bot : bots) {
				if (bot != nullptr &&
					bot->coord() == Coordinate{ x,y })
				{
					std::cout << "{}";
					printed = true;
					break;
				}
			}
			if (printed) continue;

			Cells c = this->maze.cellType(y,x);
			switch (c) {
				case path:
					std::cout << " ";
					break;
				case wall:
					std::cout << char(254);
					break;
				case start:
					std::cout << "+";
					break;
				case end:
					std::cout << "*";
					break;
				case boundary:
					std::cout << "#";
					break;
			}
			if (printed) continue;
			else std::cout << " ";
		}
		std::cout << std::endl;
	}
}


void Game::processBots(int frame) {
	if (frame == 0) {
		for (const auto& bot : bots) {
			if (bot != nullptr) {
				bot->pathFind(this->maze, this->user->coord());
			}
		}
	}
	else if (frame % 2 == 0 || frame % 3 == 0) {
		for (const auto& bot : bots) {
			if (bot != nullptr) {
				if (distance(bot->coord(), this->user->coord()) < COLLISION_DISTANCE) {
					collisionCheck(bot);
				}
					bot->move();
			}
		}
	}
}

