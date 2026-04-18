#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinate {
	public:
		float x;
		float y;

		Coordinate(const float& = 0, const float& = 0);
		Coordinate(const Coordinate&);
		Coordinate(Coordinate&&) noexcept ;
		bool operator == (const Coordinate&) const;
		bool operator == (Coordinate&&) const;
		bool operator != (Coordinate&&) const;
		void operator = (const Coordinate&);
};


#endif // COORDINATES_H