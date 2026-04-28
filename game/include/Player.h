#ifndef USER_H
#define USER_H

#include "Core.h"
#include "Render.h"

constexpr const char* PLAYER_IDLE_SPRITE_PATH = "../assets/player_idle.png";
constexpr const char* PLAYER_RUN_SPRITE_PATH = "../assets/player_run.png";
constexpr const char* PLAYER_HEART_PATH = "../assets/heart.png";
constexpr const char* PLAYER_KEY_PATH = "../assets/key.png";
constexpr const char* PLAYER_HURT_SPRITE_PATH = "../assets/player_hurt.png";
constexpr float stateUpdateTime = 800.0f;

struct Player {
	Character* character;
	std::vector<Sprite*> characterSprite;
	Texture* heart;
	Texture* key;
	static float stateTimer;

	Player(SDL_Renderer*, const Coordinate&);
	~Player();

	void update(enum PlayerStates);
	void updateTimer(const float&);
	void render(SDL_Renderer*, Camera* camera, const unsigned char&);
	void move(Maze*, const float&);
};

#endif // ! USER_H