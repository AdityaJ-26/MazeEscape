#include <iostream>
#include "SDL.h"

#include "..\include\game.h"
#include "..\include\constants.h"
#include <Windows.h>

Game::Game() 
	: maze(MAZE_SIZE),
	  running(true),
	  user(new Player(this->maze.getStartPoint()))
	  /*obj(MAX_OBJECTIVE, nullptr)*/ {
}

void Game::handleEvents() {
	const Coordinate c = this->user->coord();
	if (GetAsyncKeyState(0x57)) {
		if (this->maze.isPath(c.x, c.y + 1)) {
			this->user->move(up);
		}
	}
	else if (GetAsyncKeyState(0x53)) {
		if (this->maze.isPath(c.x , c.y - 1)) {
			this->user->move(down);
		}
	}
	else if (GetAsyncKeyState(0x41)) {
		if (this->maze.isPath(c.x - 1, c.y)) {
			this->user->move(left);
		}
	}
	else if (GetAsyncKeyState(0x44)) {
		if (this->maze.isPath(c.x + 1, c.y)) {
			this->user->move(right);
		}
	}
}
void Game::print() {
	this->maze.print();
}

void Game::update() {
	this->maze.playerPosition(this->user->coord());
}

