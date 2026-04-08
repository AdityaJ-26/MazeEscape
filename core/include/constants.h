#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

namespace Constant{
	constexpr int32_t MAX_LIVES = 3;
	constexpr int32_t MAZE_SIZE = 39;
	constexpr int32_t MAX_KEYS = 4;
	
	constexpr double PROBABILITY_FACTOR = 0.06;
	
	constexpr int32_t ENTITY_WIDTH = 1;
	constexpr int32_t ENTITY_HEIGHT = 1;

	constexpr int32_t PLAYER_DISTANCE = 30;
	constexpr double BOT_SPEED = 0.2;

	constexpr double SPEED = 0.5;
}

enum Cells {
	wall = 0,
	way = 1,
	start = 2,
	end = 3,
	boundary = -1
};

enum PlayerStates {
	idle,
	interact,
	move,
};

enum Direction {
	up,
	down,
	left,
	right
};

#endif // CONSTANTS_H
