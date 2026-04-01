#include <iostream>
#include <random>

#include "game.h"

/* -------------------------------------------------- */
// Constructor | Destructor
/* -------------------------------------------------- */
Game::Game() :
	maze(MAZE_SIZE),
	running(true),
	user(new Player(this->maze.getStartPoint())),
	keys(MAX_KEYS, nullptr),
	app(new App()),
	textures(new Texture())
{
	spawnKeys();
	app->App_Init();
	textures->load(app->renderer);
}

Game::~Game() {
	for (auto& key : keys) {
		delete key;
		key = nullptr;
	}
	delete user;
	user = nullptr;
	delete textures;
	delete app;
}


/* -------------------------------------------------- */
// Input
/* -------------------------------------------------- */
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		const Coordinate c = this->user->coord();
		if (event.type == SDL_QUIT) {
			running = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_UP:
					if (isMovable(c.x - 1, c.y)) {
						this->user->setState(move_up);
					}
					break;
				case SDLK_LEFT:
					if (isMovable(c.x, c.y - 1)) {
						this->user->setState(move_left);
					}
					break;
				case SDLK_DOWN:
					if (isMovable(c.x + 1, c.y)) {
						this->user->setState(move_down);
					}
					break;
				case SDLK_RIGHT:
					if (isMovable(c.x, c.y + 1)) {
						this->user->setState(move_right);
					}
					break;
				case SDLK_ESCAPE:
					this->running = false;
					break;
				case SDLK_SPACE:
					this->user->setState(interacting);
			}
		}
	}
}


/* -------------------------------------------------- */
// Rendering
/* -------------------------------------------------- */
void Game::render() {
	for (int32_t i{ 0 }; i < MAZE_SIZE; i++) {
		for (int32_t j{ 0 }; j < MAZE_SIZE; j++) {
			if (this->user->coord() == Coordinate{ i, j }) {
				std::cout << "[]";
				continue;
			}

			bool printed = false;
			for (const auto& key : keys) {
				if (key != nullptr &&
					key->coord() == Coordinate{ i, j }) 
				{
					std::cout << "? ";
					printed = true;
					break;
				}
			}

			if (printed) continue;

			Cells c = this->maze.cellType(i, j);
			switch (c) {
				case path:
					//std::cout << " ";
					break;
				case wall:
					//std::cout << char(254);
					break;
				case start:
					//std::cout << "+";
					break;
				case end:
					std::cout << "*";
					break;
				case boundary:
					//std::cout << "#";
					break;
			}

			if (printed) continue;
			else std::cout << " ";
		}
		std::cout << std::endl;
	}
}


/* -------------------------------------------------- */
// Update | Processing
/* -------------------------------------------------- */
void Game::update() {
	processPlayer();
}

void Game::processPlayer() {
	PlayerStates state = this->user->currentState();
	if (state == idle) {
		return;
	}
	else if (state == interacting) {
		if (this->user->coord() == this->maze.getEndPoint() &&
			this->user->canUnlock()) 
		{
			this->running = false;
		}
		for (auto& key : keys) {
			if (key != nullptr && key->coord() == user->coord()) {
				user->collectKey();
				delete(key);
				key = nullptr;
			}
		}
	}
	else {
		switch (state) {
			case move_up:
				this->user->move(up);
				break;
			case move_down:
				this->user->move(down);
				break;
			case move_left:
				this->user->move(left);
				break;
			case move_right:
				this->user->move(right);
				break;
		}
	}
	this->user->setState(idle);
}


/* -------------------------------------------------- */
// Spawn
/* -------------------------------------------------- */
void Game::spawnKeys() {
	std::default_random_engine engine(int(time(0)));
	std::uniform_int_distribution dist(1, this->maze.size() - 2);

	int32_t count = 0;
	while (count < MAX_KEYS) {
		int32_t x = dist(engine);
		int32_t y = dist(engine);
		if (this->maze.cellType(x, y) == path &&
			this->user->coord() != Coordinate{ x, y })
		{
			keys[count++] = new Key{ x, y };
		}
	}
}


/* -------------------------------------------------- */
// Checks
/* -------------------------------------------------- */
bool Game::isMovable(int32_t x, int32_t y) const {
	if (this->maze.cellType(x, y) != wall &&
		this->maze.cellType(x, y) != boundary)
		{
			return true;
	}
	return false;
}


/* -------------------------------------------------- */
// Init | Assets | Window | Renderer
/* -------------------------------------------------- */
void Game::render(int) {
	
	SDL_Rect* rect = new SDL_Rect{};
	rect->h = TILE_SIZE;
	rect->w = TILE_SIZE;

	SDL_RenderClear(app->renderer);

	for (int i{ 0 }; i < this->maze.size(); i++) {
		for (int j{ 0 }; j < this->maze.size(); j++) {
			rect->x = j * TILE_SIZE;
			rect->y = i * TILE_SIZE;
			if (this->user->coord() == Coordinate{ i, j }) {
				app->render(textures->player, rect);
			}
			else if (this->maze.cellType(i, j) == wall) {
				app->render(textures->wall, rect);
			}
			else if (this->maze.cellType(i, j) == path) {
				app->render(textures->path, rect);
			}
			for (const auto& key : keys) {
				if ( key != nullptr && key->coord() == Coordinate{i, j}) {
					app->render(textures->key, rect);
					break;
				}
			}
		}
	}
	SDL_RenderPresent(app->renderer);
}