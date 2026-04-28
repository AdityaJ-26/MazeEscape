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
	running(true),
	won(false)
{
	renderer = renderer_init(window);
	map = new Map(this->renderer);
	player = new Player(renderer, map->maze->getStartPoint());
	camera = new Camera((map->maze->size() * TILE_SIZE) - TILE_SIZE / 2);
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

		if (player->character->currentState() == hurt) break;

		if (event.type == SDL_QUIT) {
			running = false;
		}

		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				player->character->setDirection(up);
				player->update(run);
				break;
			case SDLK_LEFT:
				player->character->setDirection(left);
				player->update(run);
				break;
			case SDLK_DOWN:
				player->character->setDirection(down);
				player->update(run);
				break;
			case SDLK_RIGHT:
				player->character->setDirection(right);
				player->update(run);
				break;
			case SDLK_ESCAPE:
				this->running = false;;
				break;
			case SDLK_SPACE:
				player->update(interact);
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			player->update(idle);
		}
	}
}


/* -------------------------------------------------- */
// Update | Processing
/* -------------------------------------------------- */
void Game::update(const double& deltaTime, const int& frame) {
	player->updateTimer(deltaTime * 1000);

	if (player->character->livesCount() == 0) {
		this->running = false;
	}

	if (player->character->currentState() == run) {
		player->character->move(*(map->maze), deltaTime);
		const Coordinate& c = player->character->coord();
	}

	else if (player->character->currentState() == interact) {
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
			int((p.x - Constant::SIZE / 2) / Constant::SIZE) - map->maze->getEndPoint().y <= 0.1f &&
			int((p.y - Constant::SIZE / 2) / Constant::SIZE) - map->maze->getEndPoint().x <= 0.1f)
		{
			this->won = true;
			this->running = false;
		}
	}
	static float timePassed = 0;
	bool updatable = false;
	if (timePassed > BOT_UPDATE) {
		timePassed = 0;
		updatable = true;
	}
	else {
		timePassed += deltaTime;
	}

	entity->moveBots(map, player, deltaTime);
	for (const auto& bot : entity->bots) {
		if (updatable) {
			bot->pathFind(*(map->maze), player->character->coord());
		}

		if (entity->distance(bot->coord(), player->character->coord()) < COLLISION_CHECK_DISTANCE) {
			if (Physics::collision(bot, player->character)) {
				player->update(hurt);
			}
		}
	}
	camera->update(player->character->coord().x, player->character->coord().y);
}


/* -------------------------------------------------- */
// render | renderer init
/* -------------------------------------------------- */
void Game::render(const unsigned char& frame) const {
	SDL_RenderClear(renderer);
	map->render(renderer, camera);
	entity->render(renderer, camera, frame);
	player->render(renderer, camera, frame);
	SDL_RenderPresent(renderer);
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


/* -------------------------------------------------- */
// public function
/* -------------------------------------------------- */
SDL_Renderer* Game::getRenderer() const {
	return this->renderer;
}