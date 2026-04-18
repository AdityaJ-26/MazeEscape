#include "Camera.h"

#include <iostream>

Camera::Camera(const float& world_end) :
	start_x{ 0 },
	start_y{ 0 },
	end_x{ DISPLAY_PIXELS },
	end_y{ DISPLAY_PIXELS },
	world_end{ world_end }
{}

void Camera::update(const float& x, const float& y) {
    const int size = 32;

    this->start_x = (x - size / 2) - DISPLAY_PIXELS / 2;
    this->start_y = (y - size / 2) - DISPLAY_PIXELS / 2;

    if (this->start_x < 0) {
        this->start_x = 0;
    }
    if (this->start_y < 0) {
        this->start_y = 0;
    }

    this->end_x = start_x + DISPLAY_PIXELS;
    this->end_y = start_y + DISPLAY_PIXELS;

    if (this->end_x > world_end) {
        end_x = world_end;
        start_x = end_x - DISPLAY_PIXELS;
    }
    if (this->end_y > world_end) {
        end_y = world_end;
        start_y = end_y - DISPLAY_PIXELS;
    }
}
