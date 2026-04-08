#ifndef COORDINATES_H
#define COORDINATES_H

#include <cstdint>

class Coordinate {
	public:
		double x;
		double y;
		Coordinate(double = 0, double = 0);
		Coordinate(const Coordinate&);
		Coordinate(Coordinate&&) noexcept ;
		bool operator == (const Coordinate&) const;
		bool operator == (Coordinate&&) const;
		bool operator != (Coordinate&&) const;
		void operator = (const Coordinate&);
};


#endif // COORDINATES_H