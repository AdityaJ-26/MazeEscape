#include "Physics.h"

#include <iostream>

bool Physics::isBlocked(const Maze& maze, const float& x, const float& y) {
	int X = static_cast<int>((x - Constant::SIZE / 2) / Constant::SIZE);
	int Y = static_cast<int>((y - Constant::SIZE / 2) / Constant::SIZE);

	return maze.cellType(Y, X) == wall;
}