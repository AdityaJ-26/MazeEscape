#include "Physics.h"

bool Physics::isBlocked(const Maze& maze, const float& x, const float& y) {
	int X = int(x / Constant::SIZE);
	int Y = int(y / Constant::SIZE);

	return (maze.cellType(Y, X) == wall || maze.cellType(Y, X) == boundary);
}
