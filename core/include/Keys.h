#ifndef KEYS_H
#define KEYS_H

#include "Coordinates.h"

class Key : private Coordinate {
	public:
		Key(const float&, const float&);
		~Key();
		const Coordinate coord() const;
};

#endif // KEYS_H