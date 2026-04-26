#include <queue>
#include <vector>

#include "Bots.h"
#include "Physics.h"
#include <iostream>

/* -------------------------------------------------- */
// constructor
/* -------------------------------------------------- */
Bot::Bot(const float& x, const float& y) :
	Coordinate(x, y)
{}

/* -------------------------------------------------- */
// shortest path finding (using BFS)
/* -------------------------------------------------- */
void Bot::pathFind(const Maze& maze, const Coordinate& target) {
	int tx;
	int ty;

	checkTarget(maze, tx, ty, target);

	int bx = int((this->x - Constant::SIZE / 2) / Constant::SIZE);
	int by = int((this->y - Constant::SIZE / 2) / Constant::SIZE);

	std::queue<std::pair<int, int>> q;
	std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze.size(), false));
	std::vector<std::vector<Coord>> parent(maze.size(), std::vector<Coord>(maze.size(), { -1, -1 }));

	std::vector<Coord> directions{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	q.push({ by, bx });
	visited[by][bx] = true;
	parent[by][bx] = { by, bx };

	bool pathFound = false;

	while (!q.empty()) {
		const auto c = q.front();
		q.pop();

		for (const Coord& dir : directions) {
			int X = c.first + dir.first;
			int Y = c.second + dir.second;

			if (X > 0 && X < maze.size() - 1 &&
				Y > 0 && Y < maze.size() - 1 &&
				maze.cellType(X, Y) != wall &&
				visited[X][Y] == false)
			{
				visited[X][Y] = true;
				parent[X][Y] = { c.first, c.second };
				
				if (X == ty && Y == tx) {
					pathFound = true;
					break;
				}
				q.push({ X,Y });
			}
 		}
		if (pathFound) {
			break;
		}
	}
	if (pathFound) {
		path.clear();
		Coord p = { ty, tx };

		while (p.first != by || p.second != bx) {
			const auto& temp = parent[p.first][p.second];

			path.push_back({p.second * Constant::SIZE + Constant::SIZE / 2, p.first * Constant::SIZE + Constant::SIZE / 2});
			p = temp;
		}

	}
}


/* -------------------------------------------------- */
// public functions
/* -------------------------------------------------- */
const Coordinate Bot::coord() const {
	return Coordinate{ x, y };
}

void Bot::move(const Maze& maze, const Coordinate& player, const float& deltaTime) {
	if (path.empty()) {
		pathFind(maze, player);
	}

	findDirection();

	float newX = this->x;
	float newY = this->y;

	switch (this->direction) {
		case up:    
			newY -= (Constant::BOT_SPEED * deltaTime);
			break;
		case down:  
			newY += (Constant::BOT_SPEED * deltaTime);
			break;
		case left:  
			newX -= (Constant::BOT_SPEED * deltaTime);
			break;
		case right: 
			newX += (Constant::BOT_SPEED * deltaTime);
			break;
	}

	if (!Physics::isBlocked(maze, newX, this->y)) {
		this->x = newX;
	}
	if (!Physics::isBlocked(maze, this->x, newY)) {
		this->y = newY;
	}
}

const Direction& Bot::facing() const {
	return this->direction;
}

/* -------------------------------------------------- */
// private funcitons
/* -------------------------------------------------- */
void Bot::findDirection() {
	if (path.empty()) {
		direction = up;
		return;
	}

	Coord next = path.back();
	float px = next.first;
	float py = next.second;

	float dx = std::fabs(this->x - px);
	float dy = std::fabs(this->y - py);

	if (dx > 2.0f) {
		direction = (px > this->x) ? right : left;
	}
	else if (dy > 2.0f) {
		direction = (py > this->y) ? down : up;
	}
	else {
		path.pop_back();
		direction = up;
	}
}


void Bot::checkTarget(const Maze& maze, int& tx, int& ty, const Coordinate& target) const {
	tx = int((target.x - Constant::SIZE / 2) / Constant::SIZE);
	ty = int((target.y - Constant::SIZE / 2) / Constant::SIZE);

	if (maze.cellType(ty, tx) == wall) {
		if (maze.cellType(ty + 1, tx) == way) {
			ty += 1;
			return;
		}
		if (maze.cellType(ty - 1, tx) == way) {
			ty -= 1;
			return;
		}
		if (maze.cellType(ty, tx + 1) == way) {
			tx += 1;
			return;
		}
		if (maze.cellType(ty, tx - 1) == way) {
			tx -= 1;
			return;
		}
	}
}

