#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player {
	private:
		Coordinate position;
		Coordinate spawnPoint;
		uint16_t lives;
		uint16_t keyCount;
	public:
		Player(Coordinate);
		void move(enum Movements);
		bool hit();
		const Coordinate& coord() const;
};

#endif // PLAYER_H