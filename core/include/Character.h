#ifndef PLAYER_H
#define PLAYER_H

#include "Coordinates.h"


class Character : private Coordinate {
	private:
		Coordinate spawnPoint;
		int32_t lives;
		int32_t keyCollected;
		enum PlayerStates state;
		enum Direction direction;

	public:
		Character(const Coordinate&);
		const Coordinate& coord();
		void setState(const PlayerStates&);
		const PlayerStates& currentState() const;
		void setDirection(const Direction&);
		const Direction& facing() const;
		void move(const double&);
		void hit();
		void collectKey();
		bool canUnlock() const;
		const int32_t& livesCount() const;
};

#endif // PLAYER_H