#include "Player.h"

#include <iostream>


/* -------------------------------------------------- */
// constructor / destructor
/* -------------------------------------------------- */
Player::Player(SDL_Renderer* renderer, const Coordinate& spawn) :
	character(new Character((spawn.y * Constant::SIZE + Constant::SIZE / 2), (spawn.x * Constant::SIZE + Constant::SIZE / 2)))
{
	for (int i{ 0 }; i < totalStates; i++) characterSprite.push_back(new Sprite());
	characterSprite[idle]->load(renderer, PLAYER_IDLE_SPRITE_PATH);
	characterSprite[run]->load(renderer, PLAYER_RUN_SPRITE_PATH);
	characterSprite[interact]->load(renderer, PLAYER_IDLE_SPRITE_PATH);
}

Player::~Player() {
	delete character;
	character = nullptr;
	for (auto& sprite : characterSprite) {
		delete sprite;
		sprite = nullptr;
	}
}


/* -------------------------------------------------- */
// render
/* -------------------------------------------------- */
void Player::render(SDL_Renderer* renderer, Camera* camera, const unsigned char& frame) {
	SDL_Rect rect;
	rect.h = int(TILE_SIZE * camera->zoom);
	rect.w = int(TILE_SIZE * camera->zoom);
	rect.x = int((character->coord().x - camera->start_x - TILE_SIZE / 2) * camera->zoom);
	rect.y = int((character->coord().y - camera->start_y - TILE_SIZE / 2) * camera->zoom);

	SDL_Rect src;
	src.h = TILE_SIZE;
	src.w = TILE_SIZE;
	src.x = frame * TILE_SIZE;
	src.y = character->facing() * TILE_SIZE;

	SDL_RenderCopy(renderer, characterSprite[character->currentState()]->sprite, &src, &rect);
}


/* -------------------------------------------------- */
// util functions
/* -------------------------------------------------- */
void Player::update(PlayerStates s) {
	this->character->setState(s);
}

void Player::move(Maze* maze, const float& deltaTime) {
	this->character->move(*maze, deltaTime);
}
