#include <iostream>
#include <stack>
#include <random>
#include <ctime>
#include <queue>

#include "..\include\maze.h"
#include "..\include\constants.h"

using Coord = std::pair<int32_t, int32_t>;

/* -------------------------------------------------- */
// Constructors
Maze::Maze(int32_t s)
	: _size(s),
	  _maze(s, std::vector<int32_t>(s, wall)),
	  endPoint(), 
	  startPoint()
{
	createLevel();
}

/* -------------------------------------------------- */
// DFS or Recursive Backtracking for maze generation
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
void Maze::setEndPoint() {
	std::default_random_engine engine((uint32_t)time(0));
	std::uniform_int_distribution dist(0, (int)this->_size - 1);

	uint16_t side = dist(engine) % 5;

	switch (side) {
		// top
		case 0:
			endPoint.x = dist(engine);
			endPoint.y = 0;
			this->_maze[endPoint.y][endPoint.x] = end;
			this->_maze[endPoint.y+1][endPoint.x] = path;
			break;
		// bottom
		case 1:
			endPoint.x = dist(engine);
			endPoint.y = this->_size - 1;
			this->_maze[endPoint.y][endPoint.x] = end;
			this->_maze[endPoint.y-1][endPoint.x] = path;
			break;
		// left
		case 2:
			endPoint.x = 0;
			endPoint.y = dist(engine);
			this->_maze[endPoint.y][endPoint.x] = end;
			this->_maze[endPoint.y][endPoint.x+1] = path;
			break;
		// right
		case 3:
			endPoint.x = this->_size - 1;
			endPoint.y = dist(engine);
			this->_maze[endPoint.y][endPoint.x] = end;
			this->_maze[endPoint.y][endPoint.x-1] = path;
			break;
		// in maze
		default:
			endPoint.x = dist(engine);
			endPoint.y = dist(engine);
			this->_maze[endPoint.y][endPoint.x] = end;
	}
}


/* -------------------------------------------------- */
// BFS for max length point from endpoint
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
				(this->_maze[x][y] != wall) &&
				(this->_maze[x][y] != boundary))
			{
				q.push({ x,y });
				distance[x][y] = distance[p.first][p.second] + 1;

				// calculate max distance point and mark starting point
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
// creater looping paths in maze
void Maze::createLoops() {
	std::default_random_engine engine(int(time(0)));
	std::uniform_int_distribution coordinate(1, this->size() - 2);
	std::uniform_real_distribution<double> probability(0, 1);

	int removal = this->size() * PROBABILITY_FACTOR;

	// randomely generate coordinatesa and check for probability for removal of loop creating wall
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
void Maze::createLevel() {
	setBoundary();
	generate();
	setEndPoint();
	createLoops();
	setStartPoint();
}


// check if is wall, and can connect two paths
bool Maze::removable(const int32_t& x, const int32_t& y) const {
	if (this->_maze[x][y] == wall) {
		if ((this->_maze[x + 1][y] == path && this->_maze[x - 1][y] == path)
			|| (this->_maze[x][y + 1] == path && this->_maze[x][y - 1] == path))
		{
			return true;
		}
	}
	return false;
}


/* -------------------------------------------------- */
// public functions
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

const int32_t& Maze::size() const {
	return this->_size;
}

const Coordinate& Maze::getStartPoint() const {
	return this->startPoint;
}

const Coordinate& Maze::getEndPoint() const {
	return this->endPoint;
}
