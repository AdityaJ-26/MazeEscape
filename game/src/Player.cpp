#include "Player.h"

/* -------------------------------------------------- */
// constructor / destructor
/* -------------------------------------------------- */
Player::Player(SDL_Renderer* renderer, const Coordinate& spawn) :
	character(new Character((spawn.y* Constant::SIZE + Constant::SIZE / 2), (spawn.x* Constant::SIZE + Constant::SIZE / 2))),
	heart(new Texture()),
	key(new Texture())
{
	for (int i{ 0 }; i < totalStates; i++) characterSprite.push_back(new Sprite());
	
	characterSprite[idle]->load(renderer, PLAYER_IDLE_SPRITE_PATH);
	characterSprite[run]->load(renderer, PLAYER_RUN_SPRITE_PATH);
	characterSprite[interact]->load(renderer, PLAYER_IDLE_SPRITE_PATH);
	characterSprite[hurt]->load(renderer, PLAYER_HURT_SPRITE_PATH);

	heart->load(renderer, PLAYER_HEART_PATH);
	key->load(renderer, PLAYER_KEY_PATH);
}

float Player::stateTimer = 0.0f;

Player::~Player() {
	delete character;
	character = nullptr;
	delete heart;
	heart = nullptr;
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
	
	// player lives heart and collected keys rendering
	rect.h = TILE_SIZE;
	rect.w = TILE_SIZE;
	rect.y = 0;
	for (int i{ 0 }; i < character->livesCount(); i++) {
		rect.x = i * TILE_SIZE;
		SDL_RenderCopy(renderer, heart->tex, nullptr, &rect); 
	}

	rect.y = TILE_SIZE;
	for (int i{ 0 }; i < character->keyCount(); i++) {
		rect.x = i * TILE_SIZE;
		SDL_RenderCopy(renderer, key->tex, nullptr, &rect);
	}
}


/* -------------------------------------------------- */
// util functions
/* -------------------------------------------------- */
void Player::updateTimer(const float& deltaTime) {
	this->stateTimer += deltaTime;
	if (stateTimer > stateUpdateTime) {
		stateTimer = 0;
		if (character->currentState() == hurt) {
			character->setState(idle);
		}
	}
}

void Player::update(PlayerStates s) {
	if (s == hurt) {
		stateTimer = 0;
		character->hit();
	}
	this->character->setState(s);
}

void Player::move(Maze* maze, const float& deltaTime) {
	this->character->move(*maze, deltaTime);
}
