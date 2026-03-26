#ifndef COORDINATE_H
#define COORDINATE_H

#include <cstdint>

class Coordinate {
	public:
		int32_t x;
		int32_t y;
		Coordinate(int32_t = 0, int32_t = 0);
		Coordinate(const Coordinate&);
		Coordinate(Coordinate&&) noexcept ;
		bool operator == (const Coordinate&) const;
		bool operator == (Coordinate&&) const;
		bool operator != (Coordinate&&) const;
		void operator = (const Coordinate&);
};


#endif // COORDINATE_H