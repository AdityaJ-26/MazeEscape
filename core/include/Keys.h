#ifndef KEYS_H
#define KEYS_H

#include "Coordinates.h"

class Key : private Coordinate {
	public:
		Key(int32_t, int32_t);
		~Key();
		const Coordinate coord() const;
};

#endif // KEYS_H