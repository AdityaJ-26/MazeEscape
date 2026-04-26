#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>

constexpr float screen_y = 1024.0f;
constexpr float screen_x = 720.0f;
constexpr float SIZE = 32;
constexpr float ZOOM = 1.0f;

struct Camera {
	float start_x;
	float start_y;
	float end_x;
	float end_y;
	float world_end;
	float zoom;

	Camera(const float&);
	~Camera() = default;

	void update(const float&, const float&);
};


#endif // ! CAMERA_H