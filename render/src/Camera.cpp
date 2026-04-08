#include "Camera.h"

Camera::Camera(const int32_t& world_start, const int32_t& world_end) :
	start_x{ 0 },
	start_y{ 0 },
	end_x{ DISPLAY_TILES },
	end_y{ DISPLAY_TILES },
	world_start{ world_start },
	world_end{ world_end }
{ }

void Camera::update(const double& x, const double& y) {
	int32_t start_x = int32_t(x - DISPLAY_TILES / 2);
	int32_t start_y = int32_t(y - DISPLAY_TILES / 2);

	if (start_x < world_start) start_x = 0;
	if (start_y < world_start) start_y = 0;

	int32_t end_x = start_x + DISPLAY_TILES - 1;
	int32_t end_y = start_y + DISPLAY_TILES - 1;

	if (end_x >= world_end) end_x = world_end - 1;
	if (end_y >= world_end) end_y = world_end - 1;
}