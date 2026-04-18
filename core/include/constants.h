#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

namespace Constant{
	constexpr unsigned char MAX_LIVES = 3;
	constexpr unsigned char MAZE_SIZE = 39;
	constexpr unsigned char MAX_KEYS = 4;
	
	constexpr float PROBABILITY_FACTOR = 0.06f;
	
	constexpr int SIZE = 32;

	constexpr unsigned char PLAYER_DISTANCE = 30;
	constexpr float BOT_SPEED = 200.0f;

	constexpr float SPEED = 300.0f;
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
