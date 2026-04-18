#include "Character.h"
#include "constants.h"
#include "Physics.h"

/* -------------------------------------------------- */
// constructor
/* -------------------------------------------------- */
Character::Character(const float& x, const float& y) :
	Coordinate(Coordinate{ x, y }),
	spawnPoint(Coordinate{ x, y }),
	lives(Constant::MAX_LIVES),
	keyCollected(0),
	state(idle),
	direction(down)
{}


/* -------------------------------------------------- */
// move
/* -------------------------------------------------- */
void Character::move(const Maze& maze, const float& dt) {

	float newX = this->x;
	float newY = this->y;

	switch (direction) {
	case up:
		newY -= Constant::SPEED * dt;
		break;
	case down:
		newY += Constant::SPEED * dt;
		break;
	case left:
		newX -= Constant::SPEED * dt;
		break;
	case right:
		newX += Constant::SPEED * dt;
		break;
	}

	if (Physics::isBlocked(maze, newX, this->y) == false) {
		this->x = newX;
	}
	if (Physics::isBlocked(maze, this->x, newY) == false) {
		this->y = newY;
	}
}

/* -------------------------------------------------- */
// public functions
/* -------------------------------------------------- */
const Coordinate Character::coord() 
	{ return Coordinate{ this->x, this->y }; }

const PlayerStates& Character::currentState() const
	{ return this->state; }

void Character::setState(const PlayerStates& s)
	{ this->state = s; }

void Character::setDirection(const Direction& direction) {
	this->direction = direction;
}

const Direction& Character::facing() const {
	return this->direction;
}

void Character::collectKey()
	{ this->keyCollected++; }

bool Character::canUnlock() const
	{ return this->keyCollected == Constant::MAX_KEYS; }

void Character::hit() {
	this->lives--;
	this->x = this->spawnPoint.x;
	this->y = this->spawnPoint.y;
}

const int& Character::livesCount() const {
	return this->lives;
}