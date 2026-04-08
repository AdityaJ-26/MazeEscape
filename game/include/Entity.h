#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

constexpr double MIN_DISTANCE = 20.0;
constexpr double COLLISION_CHECK_DISTANCE = 3.0;
constexpr double KEY_SPAWN_DISTANCE = 15.0;
constexpr const char* KEY_PNG_PATH = "../assets/key.png";
constexpr const char* BOT_PNG_PATH = "../assets/bot.png";

#include "Core.h"
#include "Render.h"
#include "Map.h"
#include "Player.h"

struct Entity {
	std::vector<Key*> keys;
	std::vector<Bot*> bots;
	Texture* keyTex;
	Texture* botTex;

	Entity(SDL_Renderer*);
	~Entity();

	void spawnBot(Map*, Player*);
	void spawnKeys(Map*, Player*);
	void moveBots(Map*, const double&);
	void render(SDL_Renderer*, Camera*) const;
	const double distance(const int32_t&, const int32_t&, const double&, const double&) const;
	const double distance(const Coordinate&, const Coordinate&) const;
};

#endif // !ENTITY_H
