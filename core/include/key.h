#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "coordinate.h"

class Key : private Coordinate {
	public:
		Key(int32_t, int32_t);
		~Key();
		const Coordinate coord() const;
};

#endif // OBJECTIVE_H