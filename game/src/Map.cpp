#include "Map.h"

Map::Map(SDL_Renderer* renderer) : 
	maze(new Maze(Constant::MAZE_SIZE)),
	wayTex(nullptr),
	wallTex(nullptr)
{
	wayTex->load(renderer, WAY_PNG_PATH);
	wallTex->load(renderer, WALL_PNG_PATH);
}

Map::~Map() {
	delete maze;
	delete wayTex;
	delete wallTex;
}

void Map::render(SDL_Renderer* renderer, Camera* camera) const {
	SDL_Rect* rect = new SDL_Rect();
	rect->h = TILE_SIZE;
	rect->w = TILE_SIZE;

	for (int32_t y{ camera->start_y }; y < camera->end_y; y++) {
		for (int32_t x{ camera->start_x }; x < camera->end_x; x++) {
			rect->x = (x - camera->start_x) * TILE_SIZE;
			rect->y = (y - camera->start_y) * TILE_SIZE;
			
			if (this->maze->cellType(y, x) == wall) {
				SDL_RenderCopy(renderer, wallTex->tex, nullptr, rect);
			}
			else if (this->maze->cellType(y, x) == way) {
				SDL_RenderCopy(renderer, wallTex->tex, nullptr, rect);
			}
		}
	}
}