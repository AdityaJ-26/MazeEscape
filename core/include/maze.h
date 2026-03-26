#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "coordinate.h"

class Maze : public Coordinate {
	private:
		std::vector<std::vector<int32_t>> _maze;
		int32_t _size;
		Coordinate endPoint;
		Coordinate startPoint;

	private:
		void generate();
		void setBoundary();
		void createLoops();
		void setEndPoint();
		void setStartPoint();
		void createLevel();

	public:
		Maze(int32_t);

		void print() const;
		bool isPath(int32_t, int32_t) const;
		uint32_t size() const;

};

#endif // MAZE_H