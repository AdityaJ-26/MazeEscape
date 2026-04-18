#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

constexpr float MIN_DISTANCE = 20.0f;
constexpr float COLLISION_CHECK_DISTANCE = 3.0f;
constexpr float KEY_SPAWN_DISTANCE = 15.0f;
constexpr const char* KEY_PNG_PATH = "../assets/key.png";
constexpr const char* BOT_PNG_PATH = "../assets/bot.png";

#include "Core.h"
#include "Render.h"
#include "Map.h"
#include "Player.h"

struct Entity {
	std::vector<Key*> keys;
	std::vector<Bot*> bots;
	Texture* keyTexture;
	Texture* botTexture;

	Entity(SDL_Renderer*);
	~Entity();

	void spawnBot(Map*, Player*);
	void spawnKeys(Map*, Player*);
	void moveBots(Map* map, Player*, const float&);
	void render(SDL_Renderer*, Camera*) const;
	const float distance(const int&, const int&, const float&, const float&) const;
	const float distance(const Coordinate&, const Coordinate&) const;
};

#endif // !ENTITY_H
