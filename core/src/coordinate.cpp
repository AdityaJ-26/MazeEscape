#include "coordinate.h"

Coordinate::Coordinate(int32_t x, int32_t y)
	: x(x),
	  y(y) { }

Coordinate::Coordinate(const Coordinate& c) 
	: x(c.x),
	  y(c.y) { }

Coordinate::Coordinate(Coordinate&& c) noexcept
	: x(c.x),
	  y(c.y) { }

bool Coordinate::operator == (const Coordinate& c) const {
	return (c.x == this->x && c.y == this->y);
}

bool Coordinate::operator == (Coordinate&& c) const {
	return (c.x == this->x && c.y == this->y);
}

bool Coordinate::operator != (Coordinate&& c) const {
	return (!this->operator==(c));
}

void Coordinate::operator = (const Coordinate& c) {
	this->x = c.x;
	this->y = c.y;
}
