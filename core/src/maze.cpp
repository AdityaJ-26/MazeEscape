#include <stack>
#include <random>
#include <ctime>
#include <queue>

#include "Maze.h"
#include "constants.h"

using Coord = std::pair<int, int>;

/* -------------------------------------------------- */
// Constructors
/* -------------------------------------------------- */
Maze::Maze(int size)
	: _size(size),
	  _maze(size, std::vector<unsigned char>(size, wall)),
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

	std::default_random_engine engine((int)time(0));

	// DFS start point
	{
		int x, y;
		std::uniform_int_distribution dist(1, int(this->_size - 2));
		x = dist(engine) | 1;
		y = dist(engine) | 1;
		st.push({ x,y });
		this->_maze[x][y] = way;
	}

	while (!st.empty()) {
		Coord XY = st.top();
		std::vector<Coord> paths;

		// get all direction paths
		for (const auto& dir : directions) {
			int X = XY.first + dir.first;
			int Y = XY.second + dir.second;

			if ((X >= 0 && X < this->_size) &&
				(Y >= 0 && Y < this->_size) &&
				this->_maze[X][Y] == wall)
			{
				paths.push_back(dir);
			}
		}

		// chose one random direction and carve path
		if (!paths.empty()) {
			std::uniform_int_distribution dist(0, (int)paths.size() - 1);
			Coord path = paths[dist(engine)];

			int wallX = XY.first + path.first / 2;
			int wallY = XY.second + path.second / 2;
			int X = XY.first + path.first;
			int Y = XY.second + path.second;

			this->_maze[wallX][wallY] = way;
			this->_maze[X][Y] = way;
			st.push({ X, Y });
		}
		else {
			st.pop();
		}
	}
}


/* -------------------------------------------------- */
// Boundary Creation
/* -------------------------------------------------- */
void Maze::setBoundary(int cell) {
	for (int i{ 0 }; i < this->_size; i++) {
		this->_maze[0][i] = cell;
		this->_maze[i][0] = cell;
		this->_maze[this->_size-1][i] = cell;
		this->_maze[i][this->_size-1] = cell;
	}
}


/* -------------------------------------------------- */
// random endpoint in maze (mostly border)
/* -------------------------------------------------- */
void Maze::setEndPoint() {
	std::default_random_engine engine((int)time(0));
	std::uniform_int_distribution dist(1, (int)this->_size - 2);

	while (true) {
		int y = dist(engine);
		int x = dist(engine);
		if (this->_maze[x][y] == way) {
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
	std::vector<std::vector<int>> distance(this->_size, std::vector<int>(this->_size, -1));

	std::vector<Coord> directions{ {1,0}, {-1,0}, {0,1}, {0,-1} };
	
	q.push({ int(endPoint.x), int(endPoint.y) });
	distance[int(endPoint.x)][int(endPoint.y)] = 0;
	int maxDistance = 0;
	
	while (!q.empty()) {
		Coord p = q.front();
		q.pop();

		// check all path from fixed point and insert into queue
		for (const auto& dir : directions) {
			int x = p.first + dir.first;
			int y = p.second + dir.second;

			if ((x > 0 && x < this->_size - 1) &&
				(y > 0 && y < this->_size - 1) &&
				(distance[x][y] == -1) &&
				 this->_maze[x][y] == way)
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
// check if is wall, and can connect two passage
/* -------------------------------------------------- */
bool Maze::removable(const int& x, const int& y) const {
	int count = 0;

	if (x > 0 && this->_maze[x - 1][y] == way) count++;
	if (x < this->_size - 1 && this->_maze[x + 1][y] == way) count++;
	if (y > 0 && this->_maze[x][y - 1] == way) count++;
	if (y < this->_size - 1 && this->_maze[x][y + 1] == way) count++;

	return count >= 2;
}


/* -------------------------------------------------- */
// create looping paths in maze
/* -------------------------------------------------- */
void Maze::createLoops() {
	std::default_random_engine engine;
	std::uniform_int_distribution dist(1, this->_size - 1);

	int removals = int(this->_size * this->_size * Constant::PROBABILITY_FACTOR);

	std::vector<Coord> walls;
	for (int i{ 0 }; i < this->_size; i++) {
		for (int j{ 0 }; j < this->_size; j++) {
			if (this->_maze[i][j] == wall) {
				walls.push_back({ i,j });
			}
		}
	}
	std::shuffle(walls.begin(), walls.end(), engine);

	for (int i{ 0 }, j{ 0 }; i < removals && j < walls.size(); i++, j++) {
		const int& y = walls[i].first;
		const int& x = walls[i].second;
		if (removable(x, y)) {
			this->_maze[x][y] = way;
			removals--;
		}
	}
}


/* -------------------------------------------------- */
// maze/level creation
/* -------------------------------------------------- */
void Maze::createLevel() {
	setBoundary(-1);
	generate();
	setEndPoint();
	createLoops();
	setStartPoint();
	setBoundary(0);
}


/* -------------------------------------------------- */
// public functions
/* -------------------------------------------------- */
enum Cells Maze::cellType(const int& x,const int& y) const {
	if (x < 0 || x >= this->_size || y < 0 || y >= this->_size) {
		exit(-1);
	}
	return enum Cells(_maze[x][y]);
}

const int& Maze::size() const
	{ return this->_size; }

const Coordinate& Maze::getStartPoint() const 
	{ return this->startPoint; }

const Coordinate& Maze::getEndPoint() const 
	{ return this->endPoint; }
