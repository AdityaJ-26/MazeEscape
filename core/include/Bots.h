#ifndef BOTS_H
#define BOTS_H

#include <vector>
#include <cstdint>

#include "Coordinates.h"
#include "Maze.h"
#include "constants.h"

using Coord = std::pair<int32_t, int32_t>;

class Bot : private Coordinate {
	private:
		Direction direction;
		std::vector<Direction> path;

	private:
		Direction findDirection(const Coord&, const Coord&) const;

	public:
		explicit Bot(int32_t, int32_t);
		const Coordinate& coord() const;
		void pathFind(const Maze&, const Coordinate&);
		void move(const double& dt);
		void changeDirection();
		const Direction& facing() const;
};

#endif // ! BOTS_H