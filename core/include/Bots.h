#ifndef BOTS_H
#define BOTS_H

#include <vector>
#include <cstdint>

#include "Coordinates.h"
#include "Maze.h"
#include "constants.h"

using Coord = std::pair<int, int>;

class Bot : private Coordinate {
	private:
		Direction direction;
		std::vector<Direction> path;

	private:
		Direction findDirection(const Coord&, const Coord&) const;

	public:
		explicit Bot(const float&, const float&);
		const Coordinate coord() const;
		void pathFind(const Maze&, const Coordinate&);
		void move(const Maze&, const Coordinate&, const float& dt);
		void changeDirection(const Maze&, const Coordinate&);
		const Direction& facing() const;
};

#endif // ! BOTS_H