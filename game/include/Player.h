#ifndef USER_H
#define USER_H

#include "Core.h"
#include "Render.h"

constexpr const char* PLAYER_IDLE_SPRITE_PATH = "../assets/player_idle.png";
constexpr const char* PLAYER_RUN_SPRITE_PATH = "../assets/player_run.png";

struct Player {
	Character* character;
	std::vector<Sprite*> characterSprite;

	Player(SDL_Renderer*, const Coordinate&);
	~Player();

	void update(enum PlayerStates);
	void render(SDL_Renderer*, Camera* camera, const unsigned char&);
	void move(Maze*, const float&);
};

#endif // ! USER_H