#ifndef MAP_H
#define MAP_H

#include "Core.h"
#include "Render.h"

constexpr const char* WALL_PNG_PATH = "../assets/wall.png";
constexpr const char* WAY_PNG_PATH = "../assets/path.png";
constexpr const char* OPEN_DOOR_PNG_PATH = "../assets/open_door.png";
constexpr const char* CLOSED_DOOR_PNG_PATH = "../assets/closed_door.png";
constexpr int GRASS_SIZE = 44;

// codeMap[binary] = decimal(int)
constexpr int codeMap[16] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 
};

struct Map {
	Maze* maze;
	Texture* wallTexture;
	Texture* wayTexture;
	Texture* closedDoor;
	Texture* openDoor;

	Map(SDL_Renderer*);
	~Map();
	void render(SDL_Renderer*, Camera*) const;
};

#endif // ! MAP_H