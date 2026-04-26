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
		std::vector<std::pair<float, float>> path;

	private:
		void findDirection();
		void checkTarget(const Maze&, int&, int&, const Coordinate&) const;

	public:
		void pathFind(const Maze&, const Coordinate&);
		explicit Bot(const float&, const float&);
		const Coordinate coord() const;
		void move(const Maze&, const Coordinate&, const float& dt);
		const Direction& facing() const;
};

#endif // ! BOTS_H