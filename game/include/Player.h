#ifndef USER_H
#define USER_H

#include "Core.h"
#include "Render.h"

constexpr const char* PLAYER_PNG_PATH = "../assets/player.png";

struct Player {
	Character* character;
	Texture* characterTex;

	Player(SDL_Renderer*, const Coordinate&);
	~Player();

	void update(enum PlayerStates);
	void render(SDL_Renderer*, Camera* camera);
};

#endif // ! USER_H