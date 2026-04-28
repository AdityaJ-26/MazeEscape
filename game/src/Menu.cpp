#include "Menu.h"

GameMenu::GameMenu() :
	gameOver(new Texture()),
	menu(new Texture()),
	gameWin(new Texture())
{ }

void GameMenu::load(SDL_Renderer* renderer) {
	menu->load(renderer, MENU_PNG_PATH);
	gameOver->load(renderer, OVER_PNG_PATH);
	gameWin->load(renderer, WIN_PNG_PATH);
}

void GameMenu::renderMenu(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.h = screen_x;
	rect.w = screen_y;
	SDL_RenderCopy(renderer, menu->tex, nullptr, &rect);
}

void GameMenu::renderOver(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.h = screen_x;
	rect.w = screen_y;
	SDL_RenderCopy(renderer, gameOver->tex, nullptr, &rect);
}

void GameMenu::renderWin(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.h = screen_x;
	rect.w = screen_y;
	SDL_RenderCopy(renderer, gameWin->tex, nullptr, &rect);
}