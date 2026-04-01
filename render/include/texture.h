#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include "SDL_image.h"

constexpr int TILE_SIZE = 32;
constexpr const char* WALL_PNG_PATH = "../assets/wall.png";
constexpr const char* PATH_PNG_PATH = "../assets/path.png";
constexpr const char* PLAYER_PNG_PATH = "../assets/player.png";
constexpr const char* KEY_PNG_PATH = "../assets/key.png";

struct Texture {
	SDL_Texture* wall;
	SDL_Texture* path;
	SDL_Texture* player;
	SDL_Texture* key;

	Texture();
	~Texture();

	void load(SDL_Renderer*);
};

#endif // ! TEXTURE_H