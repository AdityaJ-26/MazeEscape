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

	// maze start point
	{
		uint32_t x, y;
		std::uniform_int_distribution dist(1, int(this->_size - 2));
		x = dist(engine) | 1;
		y = dist(engine) | 1;
		st.push({ y,x });
		this->_maze[y][x] = path;
	}

	while (!st.empty()) {
		Coord XY = st.top();

		std::vector<Coord> paths;

		// get all direction paths
		for (const auto& dir : directions) {
			int32_t newY = XY.first + dir.first;
			int32_t newX = XY.second + dir.second;

			if ((newX >= 0 && newX < this->_size) &&
				(newY >= 0 && newY < this->_size) &&
				this->_maze[newY][newX] == wall)
			{
				paths.push_back(dir);
			}
		}

		//chose random direction for path
		if (!paths.empty()) {
			std::uniform_int_distribution dist(0, (int)paths.size() - 1);
			Coord way = paths[dist(engine)];

			int32_t wallY = XY.first + way.first / 2;
			int32_t wallX = XY.second + way.second / 2;
			int32_t nY = XY.first + way.first;
			int32_t nX = XY.second + way.second;

			this->_maze[wallY][wallX] = path;
			this->_maze[nY][nX] = path;
			st.push({ nY, nX });
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
	
	q.push({ endPoint.y, endPoint.x });
	distance[endPoint.y][endPoint.x] = 0;
	int maxDistance = 0;
	
	while (!q.empty()) {
		Coord p = q.front();
		q.pop();

		for (const auto& dir : directions) {
			int32_t y = p.first + dir.first;
			int32_t x = p.second + dir.second;

			if ((x > 0 && x < this->size() - 1) &&
				(y > 0 && y < this->size() - 1) &&
				(distance[y][x] == -1) &&
				(this->_maze[y][x] != wall)) 
			{
				q.push({ y,x });
				distance[y][x] = distance[p.second][p.first] + 1;

				if (distance[y][x] > maxDistance) {
					maxDistance = distance[y][x];
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
	std::default_random_engine engine(uint32_t(time(0)));
	std::uniform_real_distribution<double> probability(0, 1);
	std::uniform_int_distribution dist(1, this->_size - 2);

	int i = this->_size / 2;
	while (i--) {
		int32_t x = dist(engine);
		int32_t y = dist(engine);
		if (this->_maze[y][x] == wall && probability(engine) > 0.5) {
			this->_maze[y][x] = path;
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

/* -------------------------------------------------- */
// printing debug
void Maze::print() const {
	for (const auto& X : _maze) {
		for (const auto& x : X) {
			if (x == path) {
				std::cout << " ";
			}
			else if (x == start) {
				std::cout << "*";
			}
			else if (x == end) {
				std::cout << "+";
			}
			else if (x == wall) {
				std::cout << char(254);
			}
			else if (x == boundary) {
				std::cout << "#";
			}
			else if (x == user) {
				std::cout << "[]";
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}


/* -------------------------------------------------- */
// public functions
bool Maze::isPath(int32_t i, int32_t j) const {
	return (this->_maze[i][j] == path);
}

int32_t Maze::size() const {
	return this->_size;
}

const Coordinate Maze::getStartPoint() const {
	return this->startPoint;
}

void Maze::playerPosition(const Coordinate& pos) {
	this->_maze[this->player.x][this->player.y] = path;
	this->player = Coordinate(pos);
	this->_maze[this->player.x][this->player.y] = user;
}