#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player : private Coordinate {
	private:
		Coordinate spawnPoint;
		uint16_t lives;
		uint16_t keyCount;
		enum PlayerStates state;

	public:
		Player(Coordinate);
		bool hit();
		void move(const enum Movement&);
		Coordinate coord() const;
		void setState(const PlayerStates&);
		const PlayerStates& currentState() const;
		void collectKey();
		bool canUnlock() const;
};

#endif // PLAYER_H