#ifndef TEXTURES_H
#define TEXTURES_H

#include "SDL.h"
#include "SDL_image.h"


struct Texture {
	SDL_Texture* tex;

	Texture();
	~Texture();

	void load(SDL_Renderer*, const char*);
};

#endif // ! TEXTURE_H