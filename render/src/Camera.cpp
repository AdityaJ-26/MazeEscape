#include "Camera.h"

/* -------------------------------------------------- */
// consturctor
/* -------------------------------------------------- */
Camera::Camera(const float& world_end) :
	start_x{ 0 },
	start_y{ 0 },
	end_x{ screen_x },
	end_y{ screen_y },
	world_end{ world_end },
    zoom{ ZOOM }
{}


/* -------------------------------------------------- */
// update camera position
/* -------------------------------------------------- */
void Camera::update(const float& x, const float& y) {
    constexpr int TILE_SIZE = 32;
    this->start_x = x - (screen_y / zoom) / 2.0f;
    this->start_y = y - (screen_x / zoom) / 2.0f;

    if (this->start_x < 0) {
        this->start_x = 0;
    }
    if (this->start_y < 0) {
        this->start_y = 0;
    }

    this->end_x = start_x + (screen_y / zoom);
    this->end_y = start_y + (screen_x / zoom);

    if (this->end_x > world_end) {
        end_x = world_end;
        start_x = end_x - (screen_y / zoom);
    }
    if (this->end_y > world_end) {
        end_y = world_end;
        start_y = end_y - (screen_x / zoom);
    }
}
