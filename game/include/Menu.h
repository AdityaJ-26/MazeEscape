#ifndef MENU_H
#define MENU_H

#include "Render.h";

constexpr const char* MENU_PNG_PATH = "../assets/menu.png";
constexpr const char* OVER_PNG_PATH = "../assets/gameover.png";

struct GameMenu {
	Texture* menu;
	Texture* gameOver;

	GameMenu();
	void load(SDL_Renderer*);
	void renderMenu(SDL_Renderer*);
	void renderOver(SDL_Renderer*);
};

#endif // ! MENU_H