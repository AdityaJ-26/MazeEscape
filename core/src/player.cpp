#include "..\include\player.h"
#include "..\include\constants.h"
#include "..\include\game.h"

Player::Player(Coordinate spawn) : 
	Coordinate(spawn),
	spawnPoint(spawn),
	lives(MAX_LIVES),
	keyCount(0),
	state(idle)
{}

void Player::move(const enum Movement& m) {
	switch (m) {
		case up:
			this->x--;
			return;
		case down:
			this->x++;
			return;
		case left:
			this->y--;
			return;
		case right:
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

Coordinate Player::coord() const {
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