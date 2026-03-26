#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int MAX_LIVES = 3;
constexpr int32_t MAZE_SIZE = 39;
constexpr int MAX_OBJECTIVE = 4;
constexpr double PROBABILITY_FACTOR = 0.3;

enum Movements {
	up,
	down,
	left,
	right
};

enum Cells {
	wall = 0,
	path = 1,
	start = 2,
	end = 3,
	boundary = -1,
	user = 7
};

#endif // CONSTANTS_H
