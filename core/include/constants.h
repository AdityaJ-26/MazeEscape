#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

/* -------------------------------------------------- */
// Core constants
/* -------------------------------------------------- */
namespace Constant{
	constexpr unsigned char MAX_LIVES = 3;
	constexpr unsigned char MAZE_SIZE = 39;
	constexpr unsigned char MAX_KEYS = 4;
	
	constexpr float PROBABILITY_FACTOR = 0.06f;
	
	constexpr float SIZE = 32;

	constexpr unsigned char PLAYER_DISTANCE = 30;
	constexpr float BOT_SPEED = 100.0f;

	constexpr float SPEED = 150.0f;
}

/* -------------------------------------------------- */
// enums
/* -------------------------------------------------- */
enum Cells {
	wall = 0,
	way = 1,
	start = 2,
	end = 3,
	boundary = -1
};

enum PlayerStates {
	idle = 0,
	run = 1,
	interact = 2,
	totalStates = 3
};

enum Direction {
	up = 0,
	down = 1,
	left = 2,
	right = 3
};

#endif // CONSTANTS_H
