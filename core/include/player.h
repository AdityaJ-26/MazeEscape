#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player : private Coordinate {
	private:
		Coordinate spawnPoint;
		uint16_t lives;
		uint16_t keyCount;
		enum PlayerStates state;
		enum Direction facing;

	public:
		Player(Coordinate);
		bool hit();
		void move(const enum Movement&);
		const Coordinate& coord();
		void setState(const PlayerStates&);
		const PlayerStates& currentState() const;
		void collectKey();
		bool canUnlock() const;
};

#endif // PLAYER_H