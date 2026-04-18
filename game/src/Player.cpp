#include "Player.h"

Player::Player(SDL_Renderer* renderer, const Coordinate& spawn) :
	character(new Character((spawn.y * Constant::SIZE ) + Constant::SIZE / 2, (spawn.x * Constant::SIZE) + Constant::SIZE / 2)),
	characterTexture(new Texture())
{
	characterTexture->load(renderer, PLAYER_PNG_PATH);
}

Player::~Player() {
	delete character;
	character = nullptr;
	delete characterTexture;
	characterTexture = nullptr;
}

void Player::render(SDL_Renderer* renderer, Camera* camera) {
	SDL_Rect* rect = new SDL_Rect();
	rect->h = TILE_SIZE;
	rect->w = TILE_SIZE;
	rect->x = static_cast<int>(character->coord().x - camera->start_x - Constant::SIZE / 2);
	rect->y = static_cast<int>(character->coord().y - camera->start_y - Constant::SIZE / 2);

	SDL_RenderCopy(renderer, characterTexture->tex, nullptr, rect);
	delete rect;
}

void Player::update(PlayerStates s) {
	this->character->setState(s);
}

void Player::move(Maze* maze, const float& deltaTime) {
	this->character->move(*maze, deltaTime);
}
