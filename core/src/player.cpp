#include "player.h"
#include "constants.h"

Player::Player(Coordinate spawn) : 
	Coordinate(spawn),
	spawnPoint(spawn),
	lives(MAX_LIVES),
	keyCount(0),
	state(idle),
	facing(south)
{}

void Player::move(const enum Movement& m) {
	switch (m) {
		case up:
			this->facing = north;
			this->x--;
			return;
		case down:
			this->facing = south;
			this->x++;
			return;
		case left:
			this->facing = west;
			this->y--;
			return;
		case right:
			this->facing = east;
			this->y++;
			return;
	}
}

bool Player::hit() {
	this->lives--;
	if (this->lives == 0) {
		return false;
	}
	return true;
}

const Coordinate& Player::coord() {
	return Coordinate{ this->x, this->y };
}

const PlayerStates& Player::currentState() const {
	return this->state;
}

void Player::setState(const PlayerStates& s) {
	this->state = s;
}

void Player::collectKey() {
	this->keyCount++;
}

bool Player::canUnlock() const {
	return (keyCount == MAX_KEYS);
}