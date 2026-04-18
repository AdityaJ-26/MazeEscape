#include "Keys.h"
#include "Maze.h"

#include <random>

Key::Key(const float& x, const float& y)
	: Coordinate(x, y) 
{}

Key::~Key() {}

const Coordinate Key::coord() const 
	{ return Coordinate{ this->x, this->y }; }