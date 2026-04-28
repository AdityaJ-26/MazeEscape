#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Map.h"
#include "Entity.h"
#include "Player.h"

constexpr float BOT_UPDATE = 2.0f;

class Game {
	private:
		Map* map;
		Player* player;
		Entity* entity;
		SDL_Renderer* renderer;
		Camera* camera;
	private:
		SDL_Renderer* renderer_init(SDL_Window*);

	public:
		bool won;
		bool running;

	public:
		Game(SDL_Window* window);
		~Game();
		void update(const double&, const int&);
		void render(const unsigned char&) const;
		void input();
		SDL_Renderer* getRenderer() const;
};


#endif // !GAME_OBJECT_H
