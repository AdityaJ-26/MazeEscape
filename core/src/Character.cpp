#include "Character.h"
#include "constants.h"


/* -------------------------------------------------- */
// constructor
/* -------------------------------------------------- */
Character::Character(const Coordinate& spawn) : 
	Coordinate(spawn),
	spawnPoint(spawn),
	lives(Constant::MAX_LIVES),
	keyCollected(0),
	state(idle),
	direction(down)
{}


/* -------------------------------------------------- */
// move
/* -------------------------------------------------- */
void Character::move(const double& dt) {
	switch (this->direction) {
		case up:
			this->y -= Constant::SPEED * dt;
			return;
		case down:
			this->y += Constant::SPEED * dt;
			return;
		case left:
			this->x -= Constant::SPEED * dt;
			return;
		case right:
			this->x += Constant::SPEED * dt;
			return;
	}
}

/* -------------------------------------------------- */
// public functions
/* -------------------------------------------------- */
const Coordinate& Character::coord() 
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

const int32_t& Character::livesCount() const {
	return this->lives;
}