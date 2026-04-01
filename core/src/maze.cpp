#include <iostream>
#include <stack>
#include <random>
#include <ctime>
#include <queue>

#include "maze.h"
#include "constants.h"


using Coord = std::pair<int32_t, int32_t>;

/* -------------------------------------------------- */
// Constructors
/* -------------------------------------------------- */
Maze::Maze(int32_t size)
	: _size(size),
	  _maze(size, std::vector<int32_t>(size, wall)),
	  endPoint(), 
	  startPoint()
{
	createLevel();
}


/* -------------------------------------------------- */
// DFS or Recursive Backtracking for maze generation
/* -------------------------------------------------- */
void Maze::generate() {
	std::vector<Coord> directions{ {2,0}, {-2,0}, {0,2}, {0,-2} };
	std::stack<Coord> st;

	std::default_random_engine engine((uint32_t)time(0));

	// DFS start point
	{
		uint32_t x, y;
		std::uniform_int_distribution dist(1, int(this->_size - 2));
		x = dist(engine) | 1;
		y = dist(engine) | 1;
		st.push({ x,y });
		this->_maze[x][y] = path;
	}

	while (!st.empty()) {
		Coord XY = st.top();

		std::vector<Coord> paths;

		// get all direction paths
		for (const auto& dir : directions) {
			int32_t newX = XY.first + dir.first;
			int32_t newY = XY.second + dir.second;

			if ((newX >= 0 && newX < this->_size) &&
				(newY >= 0 && newY < this->_size) &&
				this->_maze[newX][newY] == wall)
			{
				paths.push_back(dir);
			}
		}

		// chose one random direction and carve path
		if (!paths.empty()) {
			std::uniform_int_distribution dist(0, (int)paths.size() - 1);
			Coord way = paths[dist(engine)];

			int32_t wallX = XY.first + way.first / 2;
			int32_t wallY = XY.second + way.second / 2;
			int32_t nX = XY.first + way.first;
			int32_t nY = XY.second + way.second;

			this->_maze[wallX][wallY] = path;
			this->_maze[nX][nY] = path;
			st.push({ nX, nY });
		}
		else {
			st.pop();
		}
	}
}


/* -------------------------------------------------- */
// Boundary Creation
/* -------------------------------------------------- */
void Maze::setBoundary() {
	for (int i{ 0 }; i < this->size(); i++) {
		this->_maze[0][i] = boundary;
		this->_maze[i][0] = boundary;
		this->_maze[this->_size-1][i] = boundary;
		this->_maze[i][this->_size-1] = boundary;
	}
}


/* -------------------------------------------------- */
// random endpoint in maze (mostly border)
/* -------------------------------------------------- */
void Maze::setEndPoint() {
	std::default_random_engine engine((uint32_t)time(0));
	std::uniform_int_distribution dist(1, (int)this->_size - 2);

	while (true) {
		int32_t x = dist(engine);
		int32_t y = dist(engine);
		if (this->_maze[x][y] == path) {
			this->endPoint.x = x;
			this->endPoint.y = y;
			this->_maze[x][y] = end;
			break;
		}
	}
}


/* -------------------------------------------------- */
// BFS for max length point from endpoint
/* -------------------------------------------------- */
void Maze::setStartPoint() {
	std::queue<Coord> q;
	std::vector<std::vector<int32_t>> distance(this->_size, std::vector<int32_t>(this->_size, -1));

	std::vector<Coord> directions{ {1,0}, {-1,0}, {0,1}, {0,-1} };
	
	q.push({ endPoint.x, endPoint.y });
	distance[endPoint.x][endPoint.y] = 0;
	int maxDistance = 0;
	
	while (!q.empty()) {
		Coord p = q.front();
		q.pop();

		// check all path from fixed point and insert into queue
		for (const auto& dir : directions) {
			int32_t x = p.first + dir.first;
			int32_t y = p.second + dir.second;

			if ((x > 0 && x < this->size() - 1) &&
				(y > 0 && y < this->size() - 1) &&
				(distance[x][y] == -1) &&
				 this->_maze[x][y] == path)
			{
				q.push({ x,y });
				distance[x][y] = distance[p.first][p.second] + 1;

				// check max distance point and update starting point
				if (distance[x][y] > maxDistance) {
					maxDistance = distance[x][y];
					startPoint.x = x;
					startPoint.y = y;
				}

			}
		}
	}
	this->_maze[startPoint.x][startPoint.y] = start;
}


/* -------------------------------------------------- */
// create looping paths in maze
/* -------------------------------------------------- */
void Maze::createLoops() {
	std::default_random_engine engine(int(time(0)));
	std::uniform_int_distribution coordinate(1, this->size() - 2);
	std::uniform_real_distribution<double> probability(0, 1);

	int removal = double(this->size() * (1 - PROBABILITY_FACTOR));

	// randomely generate coordinates and check for probability for removal of loop creating wall
	while (removal > 0) {
		if (probability(engine) <= PROBABILITY_FACTOR) {
			int32_t x = coordinate(engine);
			int32_t y = coordinate(engine);
			if (this->removable(x, y)) {
				this->_maze[x][y] = path;
				removal--;
			}
		}
	}

}


/* -------------------------------------------------- */
// maze/level creation
/* -------------------------------------------------- */
void Maze::createLevel() {
	setBoundary();
	generate();
	setEndPoint();
	createLoops();
	setStartPoint();
}

/* -------------------------------------------------- */
// check if is wall, and can connect two passage
/* -------------------------------------------------- */
bool Maze::removable(const int32_t& x, const int32_t& y) const {
	int32_t xCount = 0, yCount = 0;
	int32_t tx = 1, ty = 1 ;
	while (true) {
		if (this->_maze[tx + x][y] == path) {
			tx++;
			xCount++;
		}
		else {
			break;
		}
	}
	ty = 1;
	while (true) {
		if (this->_maze[x][y + ty] == path) {
			ty++;
			yCount++;
		}
		else {
			break;
		}
	}
	if (xCount > 3 || yCount > 3) {
		return true;
	}

	tx = 1;
	xCount = 0, yCount = 0;
	while (true) {
		if (this->_maze[x - tx][y] == path) {
			tx++;
			xCount++;
		}
		else {
			break;
		}
	}
	ty = 1;
	while (true) {
		if (this->_maze[x][y - ty] == path) {
			ty++;
			yCount++;
		}
		else {
			break;
		}
	}
	if (xCount > 3 || yCount > 3) {
		return true;
	}
	return false;
}


/* -------------------------------------------------- */
// public functions
/* -------------------------------------------------- */
enum Cells Maze::cellType(const int32_t& i,const int32_t& j) const {
	switch (this->_maze[i][j]) {
		case 1:
			return path;
		case 0:
			return wall;
		case 2:
			return start;
		case 3:
			return end;
		default:
			return boundary;
	}
}

const int32_t& Maze::size() const 
	{ return this->_size; }

const Coordinate& Maze::getStartPoint() const 
	{ return this->startPoint; }

const Coordinate& Maze::getEndPoint() const 
	{ return this->endPoint; }
