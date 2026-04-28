#ifndef MENU_H
#define MENU_H

#include "Render.h";

constexpr const char* MENU_PNG_PATH = "../assets/menu.png";
constexpr const char* OVER_PNG_PATH = "../assets/game_over.png";
constexpr const char* WIN_PNG_PATH = "../assets/game_win.png";

struct GameMenu {
	Texture* menu;
	Texture* gameOver;
	Texture* gameWin;

	GameMenu();
	void load(SDL_Renderer*);
	void renderMenu(SDL_Renderer*);
	void renderOver(SDL_Renderer*);
	void renderWin(SDL_Renderer*);
};

#endif // ! MENU_H