#include <iostream>

#include "assets.h"

Surfaces::Surfaces() : windowSurface() {}
Surfaces::~Surfaces() {
	windowSurface = nullptr;
}
