#include "..\include\player.h"
#include "..\include\constants.h"
#include "..\include\game.h"
#include "..\include\functions.h"

Player::Player(Coordinate spawn) 
	: spawnPoint(spawn),
	  position(spawn),
	  lives(MAX_LIVES),
	  keyCount(0) {
}

void Player::move(enum Movements m) {
	switch (m) {
		case up:
			this->position.y++;
			break;
		case down:
			this->position.y--;
			break;
		case left:
			this->position.x--;
			break;
		case right:
			this->position.x++;
			break;
		default:
			break;
	}
}

bool Player::hit() {
	this->lives--;
	if (this->lives == 0) {
		return false;
	}
	return true;
}

const Coordinate& Player::coord() const {
	return position;
}