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
		enum Cells cellType(const int32_t&, const int32_t&) const;
		const int32_t& size() const;
		const Coordinate& getStartPoint() const;
		const Coordinate& getEndPoint() const;
};

#endif // MAZE_H