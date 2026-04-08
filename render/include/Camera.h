#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>

constexpr int32_t DISPLAY_TILES = 23;

struct Camera {
	int32_t start_x;
	int32_t start_y;
	int32_t end_x;
	int32_t end_y;
	int32_t world_start;
	int32_t world_end;

	Camera(const int32_t&, const int32_t&);
	~Camera() = default;

	void update(const double&, const double&);
};


#endif // ! CAMERA_H