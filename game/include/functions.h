#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL.h"
#include "SDL_image.h"

constexpr const char* TITLE = "MazeEscape";
constexpr const int SCREEN_WIDTH = 800;
constexpr const int SCREEN_HEIGHT = 600;

void init();
SDL_Window* window_init();

#endif // !FUNCTIONS_H
