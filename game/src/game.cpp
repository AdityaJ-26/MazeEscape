#include <iostream>
#include <Windows.h>
#include <random>

#include "game.h"

Game::Game() :
	maze(MAZE_SIZE),
	running(true),
	user(new Player(this->maze.getStartPoint())),
	keys(MAX_KEYS, nullptr),
	surfaces(nullptr),
	window(nullptr)
{
	spawnKeys();
	init();
}


bool Game::inBound(int32_t x, int32_t y) const {
	return ((x >= 0 && x < MAZE_SIZE) && (y >= 0 && y < MAZE_SIZE));
}


// input handling with bound checking
//void Game::handleEvents() {
//	const Coordinate c = this->user->coord();
//	// w
//	if (GetAsyncKeyState(0x57)) {
//		if (inBound(c.x + 1, c.y) && 
//			(this->maze.cellType(c.x - 1, c.y) != wall &&
//			this->maze.cellType(c.x - 1, c.y) != boundary))
//		{
//			this->user->setState(move_up);
//		}
//	}
//	// a
//	else if (GetAsyncKeyState(0x41)) {
//		if (inBound(c.x, c.y - 1) &&
//			(this->maze.cellType(c.x, c.y - 1) != wall &&
//			this->maze.cellType(c.x, c.y - 1) != boundary)) 
//		{
//			this->user->setState(move_left);
//		}
//	}
//	// s
//	else if (GetAsyncKeyState(0x53)) {
//		if (inBound(c.x - 1, c.y) && 
//			(this->maze.cellType(c.x + 1, c.y) != wall &&
//			this->maze.cellType(c.x + 1 , c.y) != boundary))
//		{
//			this->user->setState(move_down);
//		}
//	}
//	// d
//	else if (GetAsyncKeyState(0x44)) {
//		if (inBound(c.x, c.y + 1) && 
//			(this->maze.cellType(c.x, c.y + 1) != wall &&
//			this->maze.cellType(c.x, c.y + 1) != boundary)) 
//		{
//			this->user->setState(move_right);
//		}
//	}
//}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		const Coordinate c = this->user->coord();
		if (event.type == SDL_QUIT) {
			running = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_w:
					if (isMovable(c.x + 1, c.y)) {
						this->user->setState(move_up);
					}
					break;
				case SDLK_a:
					if (isMovable(c.x, c.y - 1)) {
						this->user->setState(move_left);
					}
					break;
				case SDLK_s:
					if (isMovable(c.x + 1, c.y)) {
						this->user->setState(move_down);
					}
					break;
				case SDLK_d:
					if (isMovable(c.x, c.y + 1)) {
						this->user->setState(move_right);
					}
					break;
				case SDLK_ESCAPE:
					this->running = false;
					break;
			}
		}
	}
}


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
					std::cout << " ";
					break;
				case wall:
					std::cout << char(254);
					break;
				case start:
					std::cout << "+";
					break;
				case end:
					std::cout << "*";
					break;
				case boundary:
					std::cout << "#";
					break;
			}

			if (printed) continue;
			else std::cout << " ";
		}
		std::cout << std::endl;
	}
	SDL_UpdateWindowSurface(window);
}


void Game::update() {
	processPlayer();
}


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


void Game::init() {

	surfaces = new Surfaces();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "_lib_error : " << SDL_GetError() << std::endl;
		exit(-1);
	}
	else {
		window = SDL_CreateWindow("MazeEscape.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cerr << "_initialising_error : " << SDL_GetError() << std::endl;
			exit(-1);
		}
		else {
			surfaces->windowSurface = SDL_GetWindowSurface(window);
		}
	}
}

bool Game::isMovable(int32_t x, int32_t y) const {
	if (inBound(x, y) &&
	   (this->maze.cellType(x, y) != wall &&
		this->maze.cellType(x, y) != boundary))
	{
		return true;
	}
	return false;
}