#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL.h"
#include "SDL_image.h"
#include "menu.h"
#include "GameObject.h"

constexpr const char* TITLE = "MazeEscape";
constexpr const int SCREEN_WIDTH = 1024;
constexpr const int SCREEN_HEIGHT = 720;

void init();
SDL_Window* window_init();

bool menuWindow(GameMenu*, SDL_Renderer*);
void gameOverWindow(GameMenu*, SDL_Renderer*);
void quit(Game*, SDL_Window*);

#endif // !FUNCTIONS_H
