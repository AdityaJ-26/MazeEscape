#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "coordinate.h"

class Maze {
	private:
		std::vector<std::vector<int32_t>> _maze;
		int32_t _size;
		Coordinate endPoint;
		Coordinate startPoint;

		Coordinate player;

	private:
		void generate();
		void setBoundary();
		void createLoops();
		void setEndPoint();
		void setStartPoint();
		void createLevel();
		bool removable(const int32_t&, const int32_t&) const;

	public:
		Maze(int32_t);

		void print() const;
		bool isPath(int32_t, int32_t) const;
		int32_t size() const;
		const Coordinate getStartPoint() const;
		void playerPosition(const Coordinate&);
};

#endif // MAZE_H