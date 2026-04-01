#ifndef APP_H
#define APP_H

#include "SDL.h"

constexpr const char* TITLE = "MazeEscape";
constexpr const int SCREEN_WIDTH = 1280;
constexpr const int SCREEN_HEIGHT = 980;

struct App {
	SDL_Window* window;
	SDL_Renderer* renderer;

	App();
	~App();

	void App_Init();
	void render(SDL_Texture*, SDL_Rect*) const;
	//void clear() const;
	//void present() const;
};

#endif // ! APP_H