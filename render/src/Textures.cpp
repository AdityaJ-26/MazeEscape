#include <iostream>

#include "Textures.h"

Texture::Texture() :
	tex(nullptr)
{ }

Texture::~Texture() {
	SDL_DestroyTexture(tex);
	tex = nullptr;
}

void Texture::load(SDL_Renderer* renderer, const char* path) {
	tex = IMG_LoadTexture(renderer, path);
}