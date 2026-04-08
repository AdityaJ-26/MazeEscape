#include "Player.h"
#include "Core.h"

Player::Player(SDL_Renderer* renderer, const Coordinate& spawn) :
	character(new Character(spawn)),
	characterTex(nullptr)
{
	characterTex->load(renderer, PLAYER_PNG_PATH);
}

Player::~Player() {
	delete character;
	character = nullptr;
	delete characterTex;
	characterTex = nullptr;
}

void Player::render(SDL_Renderer* renderer, Camera* camera) {
	SDL_Rect* rect = new SDL_Rect();
	rect->h = TILE_SIZE;
	rect->w = TILE_SIZE;
	rect->x = static_cast<int>((character->coord().x - camera->start_x) * TILE_SIZE);
	rect->y = static_cast<int>((character->coord().y - camera->start_y) * TILE_SIZE);

	SDL_RenderCopy(renderer, characterTex->tex, nullptr, rect);
	delete rect;
}

void Player::update(PlayerStates s) {
	this->character->setState(s);
}

