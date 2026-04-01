#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"

class Player : private Coordinate {
	private:
		Coordinate spawnPoint;
		int32_t lives;
		int32_t keyCount;
		enum PlayerStates state;
		enum Direction facing;

	public:
		Player(Coordinate);
		const Coordinate& coord();
		void setState(const PlayerStates&);
		const PlayerStates& currentState() const;
		void move(const enum Movement&);
		bool hit();
		void collectKey();
		bool canUnlock() const;
};

#endif // PLAYER_H