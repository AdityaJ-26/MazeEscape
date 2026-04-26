#include "Map.h"


/* -------------------------------------------------- */
// constructor / destructor
/* -------------------------------------------------- */
Map::Map(SDL_Renderer* renderer) : 
	maze(new Maze(Constant::MAZE_SIZE)),
	wayTexture(new Texture),
	wallTexture(new Texture)
{
	wayTexture->load(renderer, WAY_PNG_PATH);
	wallTexture->load(renderer, WALL_PNG_PATH);
}

Map::~Map() {
	delete maze;
	delete wayTexture;
	delete wallTexture;
}

/* -------------------------------------------------- */
// render
/* -------------------------------------------------- */
void Map::render(SDL_Renderer* renderer, Camera* camera) const {
    SDL_Rect rect;
    rect.w = TILE_SIZE * camera->zoom;
    rect.h = TILE_SIZE * camera->zoom;

    int startTileX = int(camera->start_x / TILE_SIZE);
    int endTileX = int(camera->end_x / TILE_SIZE);
    int startTileY = int(camera->start_y / TILE_SIZE);
    int endTileY = int(camera->end_y / TILE_SIZE);

    for (int y = startTileY; y <= endTileY; y++) {
        for (int x = startTileX; x <= endTileX; x++) {
            rect.x = int(x * TILE_SIZE - camera->start_x ) * camera->zoom;
            rect.y = int(y * TILE_SIZE - camera->start_y ) * camera->zoom;

            if (maze->cellType(y, x) == wall) {
                SDL_RenderCopy(renderer, wallTexture->tex, nullptr, &rect);
            }
            else if (maze->cellType(y, x) == way) {
                SDL_RenderCopy(renderer, wayTexture->tex, nullptr, &rect);
            }
            
        }
    }
}