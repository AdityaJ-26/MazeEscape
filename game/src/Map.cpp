#include "Map.h"


/* -------------------------------------------------- */
// constructor / destructor
/* -------------------------------------------------- */
Map::Map(SDL_Renderer* renderer) :
    maze(new Maze(Constant::MAZE_SIZE)),
    wayTexture(new Texture),
    wallTexture(new Texture),
    openDoor(new Texture),
    closedDoor(new Texture)
{
	wayTexture->load(renderer, WAY_PNG_PATH);
	wallTexture->load(renderer, WALL_PNG_PATH);
    openDoor->load(renderer, OPEN_DOOR_PNG_PATH);
    closedDoor->load(renderer, CLOSED_DOOR_PNG_PATH);
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
            rect.x = int(x * TILE_SIZE - camera->start_x) * camera->zoom;
            rect.y = int(y * TILE_SIZE - camera->start_y) * camera->zoom;

            SDL_RenderCopy(renderer, wayTexture->tex, nullptr, &rect);
            switch (maze->cellType(y, x)) {
                case wall:
                    SDL_RenderCopy(renderer, wallTexture->tex, nullptr, &rect);
                    break;
                case start:
                    SDL_RenderCopy(renderer, openDoor->tex, nullptr, &rect);
                    break;
                case end:
                    SDL_RenderCopy(renderer, closedDoor->tex, nullptr, &rect);
                    break;
            }
        }
    }
}