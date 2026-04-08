#ifndef MAP_H
#define MAP_H

#include "Core.h"
#include "Render.h"

constexpr const char* WALL_PNG_PATH = "../assets/wall.png";
constexpr const char* WAY_PNG_PATH = "../assets/path.png";

struct Map {
	Maze* maze;
	Texture* wallTex;
	Texture* wayTex;

	Map(SDL_Renderer*);
	~Map();
	void render(SDL_Renderer*, Camera*) const;
};

#endif // ! MAP_H