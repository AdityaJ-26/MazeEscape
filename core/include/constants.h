#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int32_t MAX_LIVES = 3;
constexpr int32_t MAZE_SIZE = 39;
constexpr int32_t MAX_KEYS = 4;
constexpr double PROBABILITY_FACTOR = 0.3;

enum Cells {
	wall = 0,
	path = 1,
	start = 2,
	end = 3,
	boundary = -1
};

enum Movement {
	up,
	down,
	left,
	right
};

enum PlayerStates {
	idle,
	interacting,
	move_up,
	move_down,
	move_left,
	move_right,
};

#endif // CONSTANTS_H
