#include <iostream>

#include "GameObject.h"
#include "Core.h"

/* -------------------------------------------------- */
// Constructor | Destructor
/* -------------------------------------------------- */
Game::Game(SDL_Window* window) :
	running(true),
	map(nullptr),
	player(nullptr),
	camera(nullptr),
	renderer(nullptr)
{
	renderer = renderer_init(window);
	map = new Map(renderer);
	player = new Player(renderer, map->maze->getStartPoint());
	camera = new Camera(0, map->maze->size()-1);
	camera->update(player->character->coord().x, player->character->coord().y);
	entity->spawnKeys(map, player);
}


Game::~Game() {
	delete map;
	delete player;
	delete entity;
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}


/* -------------------------------------------------- */
// Input
/* -------------------------------------------------- */
void Game::input() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			running = false;
		}

		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				player->update(move);
				player->character->setDirection(up);
				break;
			case SDLK_LEFT:
				player->update(move);
				player->character->setDirection(left);
				break;
			case SDLK_DOWN:
				player->update(move);
				player->character->setDirection(down);
				break;
			case SDLK_RIGHT:
				player->update(move);
				player->character->setDirection(right);
				break;
			case SDLK_ESCAPE:
				this->running = false;;
				break;
			case SDLK_SPACE:
				player->update(move);
				break;
			}
		}
	}
}



/* -------------------------------------------------- */
// Update | Processing
/* -------------------------------------------------- */
void Game::update(const double& deltaTime) {
	Physics::move(map->maze, player->character, deltaTime);

	if (player->character->currentState() == interact) {

		for (auto& key : entity->keys) {

			if (key == nullptr) continue;

			if (Physics::collision(key, player->character)) {
				player->character->collectKey();
				entity->spawnBot(map, player);
				delete key;
				key = nullptr;
			}

		}

		if (player->character->canUnlock() && player->character->coord() == map->maze->getEndPoint()) {
			this->running = false;
		}
	}
	camera->update(player->character->coord().x, player->character->coord().y);
}


/* -------------------------------------------------- */
// Init | Assets | Window | Renderer
/* -------------------------------------------------- */
void Game::render() const {
	SDL_RenderClear(renderer);
	map->render(renderer, camera);
	entity->render(renderer, camera);
	player->render(renderer, camera);
	SDL_RenderPresent(renderer);
}


SDL_Renderer* Game::renderer_init(SDL_Window* window) {
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		std::cerr << "_renderer_error : " << SDL_GetError() << std::endl;
		exit(-1);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
