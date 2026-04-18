#ifndef PLAYER_H
#define PLAYER_H

#include "Coordinates.h"
#include "Maze.h"

class Character : private Coordinate {
	private:
		Coordinate spawnPoint;
		unsigned char lives;
		unsigned char keyCollected;
		enum PlayerStates state;
		enum Direction direction;

	public:
		Character(const float&, const float&);
		const Coordinate coord();
		void setState(const PlayerStates&);
		const PlayerStates& currentState() const;
		void setDirection(const Direction&);
		const Direction& facing() const;
		void move(const Maze&, const float&);
		void hit();
		void collectKey();
		bool canUnlock() const;
		const int& livesCount() const;
};

#endif // PLAYER_H