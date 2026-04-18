#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "Coordinates.h"

class Maze {
	private:
		std::vector<std::vector<unsigned char>> _maze;
		int _size;
		Coordinate endPoint;
		Coordinate startPoint;

	private:
		void generate();
		void setBoundary();
		void createLoops();
		void setEndPoint();
		void setStartPoint();
		void createLevel();
		bool removable(const int&, const int&) const;

	public:
		Maze(int);
		enum Cells cellType(const int&, const int&) const;
		const int& size() const;
		const Coordinate& getStartPoint() const;
		const Coordinate& getEndPoint() const;
};

#endif // MAZE_H