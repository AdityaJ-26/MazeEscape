#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Map.h"
#include "Entity.h"
#include "Player.h"

const double botFrameTime = 24 / 1000;

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
		bool running;

	public:
		Game(SDL_Window* window);
		~Game();
		void update(const double&);
		void render() const;
		void render(int) const;
		void input();
};


#endif // !GAME_OBJECT_H
