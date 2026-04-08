#include <queue>
#include <vector>

#include "Bots.h"
#include "constants.h"


/* -------------------------------------------------- */
// constructor
/* -------------------------------------------------- */
Bot::Bot(int32_t x, int32_t y) :
	Coordinate(x, y),
	direction(up)
{ }


/* -------------------------------------------------- */
// shortest path finding (using BFS)
/* -------------------------------------------------- */
void Bot::pathFind(const Maze& maze, const Coordinate& target) {
	std::vector<Coord> directions{ {1,0}, {-1,0}, {0,1}, {0,-1} };

	std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze.size(), false));
	std::vector<std::vector<Coord>> parent(maze.size(), std::vector<Coord>(maze.size(), { -1, -1 }));

	std::queue<Coord> q;
	q.push({ static_cast<int32_t>(this->y), static_cast<int32_t>(this->x) });
	visited[static_cast<int32_t>(this->y)][static_cast<int32_t>(this->x)] = true;

	bool pathFound = false;

	while (!q.empty() && !pathFound) {
		Coord p = q.front();
		q.pop();

		for (const auto& dir : directions) {
			int X = dir.first + p.first;
			int Y = dir.second + p.second;
			
			if (X > 0 && X < maze.size() - 1 &&
				Y > 0 && Y < maze.size() - 1 &&
				maze.cellType( X,Y ) == way &&
				visited[X][Y] == false)
			{
				visited[X][Y] = true;
				parent[X][Y] = { p.first, p.second };

				if (X == target.y && Y == target.x)
				{
					pathFound = true;
					break;
				}
				q.push({ X,Y });
			}
		}
	}

	if (pathFound) {
		this->path.clear();

		Coord p = { target.y, target.x };

		while (p.first != this->y || p.second != this->x) {
			Coord nextP = parent[p.first][p.second];
			const Direction& d = findDirection(p, {nextP.second, nextP.first});
			if (d != path.back()) {
				p = nextP;
			}
		}
	}
	this->direction = path.back();
	path.pop_back();
}


/* -------------------------------------------------- */
// public functions
/* -------------------------------------------------- */
const Coordinate& Bot::coord() const {
	return Coordinate{ this->x, this->y };
}

void Bot::move(const double& dt) {
	if (path.empty()) return;

	switch (direction) {
		case up:
			this->y -= Constant::BOT_SPEED * dt;
			break;
		case down:
			this->y += Constant::BOT_SPEED * dt;
			break;
		case left:
			this->x -= Constant::BOT_SPEED * dt;
			break;
		case right:
			this->x += Constant::BOT_SPEED * dt;
			break;
	}
	path.pop_back();
}

const Direction& Bot::facing() const {
	return this->direction;
}

Direction Bot::findDirection(const Coord& p1, const Coord& p2) const {
	if (p1.first - 1 == p2.first) {
		return up;
	}
	else if (p1.first + 1 == p2.first) {
		return down;
	}
	else if (p1.second - 1 == p2.second) {
		return left;
	}
	else if (p1.second + 1 == p2.second) {
		return right;
	}
}

void Bot::changeDirection() {
	this->direction = path.back();
	path.pop_back();
}