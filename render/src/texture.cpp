#include <iostream>

#include "texture.h"

Texture::Texture() :
	wall(nullptr),
	path(nullptr),
	player(nullptr),
	key(nullptr)
{ }

Texture::~Texture() {
	SDL_DestroyTexture(wall);
	wall = nullptr;
	SDL_DestroyTexture(path);
	path = nullptr;
	SDL_DestroyTexture(player);
	player = nullptr;
	SDL_DestroyTexture(key);
	key = nullptr;
}

void Texture::load(SDL_Renderer* renderer) {
	wall = IMG_LoadTexture(renderer, WALL_PNG_PATH);
	if (wall == nullptr) {
		std::cerr << "_texture_error : " << SDL_GetError() << std::endl;
		exit(-1);
	}
	path = IMG_LoadTexture(renderer, PATH_PNG_PATH);
	if (path == nullptr) {
		std::cerr << "_texture_error : " << SDL_GetError() << std::endl;
	}
	player = IMG_LoadTexture(renderer, PLAYER_PNG_PATH);
	if (player == nullptr) {
		std::cerr << "_texture_error : " << SDL_GetError() << std::endl;
	}
	key = IMG_LoadTexture(renderer, KEY_PNG_PATH);
	if (key == nullptr) {
		std::cerr << "_texture_error : " << SDL_GetError() << std::endl;
	}
}