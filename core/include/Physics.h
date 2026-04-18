#ifndef PHYSICS_H
#define PHYSICS_H

#include "Maze.h"
#include "Character.h"
#include "Coordinates.h"
#include <cmath>

#include "constants.h"

struct Rect {
	int top;
	int bottom;
	int left;
	int right;

	Rect(const float& x, const float& y) {
		top = static_cast<int>(std::floor((y - Constant::SIZE / 2) / Constant::SIZE));
		bottom = static_cast<int>(std::floor((y + Constant::SIZE / 2) / Constant::SIZE));
		left = static_cast<int>(std::floor((x - Constant::SIZE / 2) / Constant::SIZE));
		right = static_cast<int>(std::floor((x + Constant::SIZE / 2) / Constant::SIZE));
	}
};

namespace Physics {
	bool isBlocked(const Maze&, const float&, const float&);

	template<typename E1,typename E2>
	// AABB collision system
	bool collision(E1* entity1, E2* entity2) {
		const Coordinate& c1 = entity1->coord();
		const Coordinate& c2 = entity2->coord();

		if (c1.x + Constant::SIZE >= c2.x &&
			c2.x + Constant::SIZE >= c1.x &&
			c2.y + Constant::SIZE >= c1.y &&
			c1.y + Constant::SIZE >= c2.y)
		{
			return true;
		}
		else {
			return false;
		}
	}

}

#endif // !PHYSICS_H
