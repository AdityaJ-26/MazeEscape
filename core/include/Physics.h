#ifndef PHYSICS_H
#define PHYSICS_H

#include "Maze.h"
#include "Character.h"
#include "Coordinates.h"
#include "constants.h"

struct Rect {
	int32_t up;
	int32_t down;
	int32_t left;
	int32_t right;

	Rect(const Coordinate& c) :
		up(static_cast<int32_t>(ceil(c.y))),
		left(static_cast<int32_t>(ceil(c.x))),
		right(static_cast<int32_t>(floor(c.x))),
		down(static_cast<int32_t>(floor(c.y)))
	{
	}
};

namespace Physics {
	template<typename Entity>
	bool move(const Maze* maze, Entity* entity, const double& deltaTime) {
		Rect* hitbox = new Rect(entity->coord());

		switch (entity->facing()) {
		case up:
		{
			if (maze->cellType(hitbox->left, hitbox->up) == wall ||
				maze->cellType(hitbox->right, hitbox->up) == wall)
			{
				return false;
			}
			else {
				entity->move(deltaTime);
			}
		}
		break;
		case down:
		{
			if (maze->cellType(hitbox->left, hitbox->down) == wall ||
				maze->cellType(hitbox->right, hitbox->down) == wall)
			{
				return false;
			}
			else {
				entity->move(deltaTime);
			}
		}
		break;
		case left:
		{
			if (maze->cellType(hitbox->left, hitbox->down) == wall ||
				maze->cellType(hitbox->left, hitbox->up) == wall)
			{
				return false;
			}
			else {
				entity->move(deltaTime);
			}
		}
		break;
		case right:
		{
			if (maze->cellType(hitbox->right, hitbox->down) == wall ||
				maze->cellType(hitbox->right, hitbox->up) == wall)
			{
				return false;
			}
			else {
				entity->move(deltaTime);
			}
		}
		break;
		}
		delete hitbox;
		return true;
	}

	template<typename E1,typename E2>
	// AABB collision system
	bool collision(E1* entity1, E2* entity2) {
		const Coordinate& c1 = entity1->coord();
		const Coordinate& c2 = entity2->coord();

		if (c1.x + Constant::ENTITY_WIDTH >= c2.x &&
			c2.x + Constant::ENTITY_WIDTH >= c1.x &&
			c2.y + Constant::ENTITY_HEIGHT >= c1.y &&
			c1.y + Constant::ENTITY_HEIGHT >= c2.y)
		{
			return true;
		}
		else {
			return false;
		}
	}

}

#endif // !PHYSICS_H
