#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>

constexpr float DISPLAY_PIXELS = 600;

struct Camera {
	float start_x;
	float start_y;
	float end_x;
	float end_y;
	float world_end;

	Camera(const float&);
	~Camera() = default;

	void update(const float&, const float&);
};


#endif // ! CAMERA_H