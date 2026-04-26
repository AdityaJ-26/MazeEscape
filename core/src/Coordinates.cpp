#include <cmath>

#include "Coordinates.h"

/* -------------------------------------------------- */
// constructors
/* -------------------------------------------------- */
Coordinate::Coordinate(const float& x, const float& y)
	: x(x),
	  y(y) 
{ }

Coordinate::Coordinate(const Coordinate& c) 
	: x(c.x),
	  y(c.y) 
{ }

Coordinate::Coordinate(Coordinate&& c) noexcept
	: x(std::move(c.x)),
	  y(std::move(c.y)) 
{ }


/* -------------------------------------------------- */
// =, ==, != operators with rhl and lhl values
/* -------------------------------------------------- */
bool Coordinate::operator == (const Coordinate& c) const 
	{ return (std::fabs(c.x - this->x < 0.1f) && std::fabs(c.y - this->y < 0.1f)); }

bool Coordinate::operator == (Coordinate&& c) const 
	{ return (std::fabs(c.x - this->x < 0.1f) && std::fabs(c.y - this->y < 0.1f)); }

bool Coordinate::operator != (Coordinate&& c) const 
	{ return (!this->operator==(c)); }

void Coordinate::operator = (const Coordinate& c) {
	this->x = c.x;
	this->y = c.y;
}
