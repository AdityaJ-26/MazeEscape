#include "key.h"
#include "maze.h"

#include <random>

Key::Key(int32_t x, int32_t y)
	: Coordinate(x, y) {}

Key::~Key() {}

const Coordinate Key::coord() const {
	return Coordinate{ this->x, this->y };
}