#ifndef SPRITES_H
#define SPRITES_H

#include "SDL.h"
#include "SDL_image.h"

struct Sprite {
	SDL_Texture* sprite;

	Sprite();
	~Sprite();

	void load(SDL_Renderer*, const char*);
};

#endif // ! SPRITES_H