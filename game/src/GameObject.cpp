#include <iostream>

#include "GameObject.h"
#include "Core.h"
#include "functions.h"

/* -------------------------------------------------- */
// Constructor | Destructor
/* -------------------------------------------------- */
Game::Game(SDL_Window* window) :
	map(nullptr),
	player(nullptr),
	entity(nullptr),
	camera(nullptr),
	renderer(nullptr),
	running(true)
{
	renderer = renderer_init(window);
	map = new Map(this->renderer);
	player = new Player(renderer, map->maze->getStartPoint());
	camera = new Camera((map->maze->size() - 1) * TILE_SIZE);
	entity = new Entity(this->renderer);
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
				player->character->setDirection(up);
				player->update(move);
				break;
			case SDLK_LEFT:
				player->character->setDirection(left);
				player->update(move);
				break;
			case SDLK_DOWN:
				player->character->setDirection(down);
				player->update(move);
				break;
			case SDLK_RIGHT:
				player->character->setDirection(right);
				player->update(move);
				break;
			case SDLK_ESCAPE:
				this->running = false;;
				break;
			case SDLK_SPACE:
				player->update(interact);
				break;
			}
		}
	}
}


/* -------------------------------------------------- */
// Update | Processing
/* -------------------------------------------------- */
void Game::update(const double& deltaTime) {
	if (player->character->currentState() == move) {
		player->character->move(*(map->maze), deltaTime);
	}

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
		const Coordinate& p = player->character->coord();
		if (player->character->canUnlock() && 
			p.x / Constant::SIZE == map->maze->getEndPoint().x &&
			p.y / Constant::SIZE == map->maze->getEndPoint().y) 
		{
			this->running = false;
		}
	}
	player->update(idle);
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


void Game::render(int) const {

	//{

	//	std::cout << "COORDINATES" << std::endl;
	//	std::cout << "Player : " << player->character->coord().x << " " << player->character->coord().y << std::endl;
	//	std::cout << "Bots : " << std::endl;
	//	for (const auto& bot : entity->bots) {
	//		std::cout << bot->coord().x << " " << bot->coord().y << std::endl;
	//	}
	//	std::cout << "Keys : " << std::endl;
	//	for (const auto& key : entity->keys) {
	//		std::cout << key->coord().x << " " << key->coord().y << std::endl;
	//	}
	//	std::cout << "Camera : " << camera->start_x << " " << camera->start_y << " " << camera->end_x << " " << camera->end_y << std::endl;
	//}



	for (int i{ 0 }; i < map->maze->size(); i++) {
		for (int j{ 0 }; j < map->maze->size(); j++) {
			if ((player->character->coord().x - Constant::SIZE / 2) / Constant::SIZE == j && 
				(player->character->coord().y - Constant::SIZE / 2) / Constant::SIZE == i) {
				std::cout << "[]";
				continue;
			}
			
			bool printed = false;
			for (const auto& key : entity->keys) {
				if (key != nullptr && 
					((key->coord().x - Constant::SIZE / 2) / Constant::SIZE == j) && 
					((key->coord().y - Constant::SIZE / 2)/ Constant::SIZE == i) )
				{
					std::cout << "+";
					printed = true;
					break;
				}
			}
			switch (map->maze->cellType(i, j)) {
			case way:
				std::cout << "  ";
				break;
			case wall:
				std::cout << char(254) << " ";
				break;
			case boundary:
				std::cout << "# ";
			}
		}
		std::cout << std::endl;
	}
}


SDL_Renderer* Game::renderer_init(SDL_Window* window) {
	if (window == nullptr) {
		std::cerr << "_null_window";
		exit(-1);
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		std::cerr << "_renderer_error : " << SDL_GetError() << std::endl;
		return nullptr;
		exit(-1);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	return renderer;
}
