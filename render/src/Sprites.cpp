#include <iostream>

#include "Sprites.h"

/* -------------------------------------------------- */
// construtor / destructor
/* -------------------------------------------------- */
Sprite::Sprite() : sprite(nullptr)
{ }

Sprite::~Sprite() {
	SDL_DestroyTexture(sprite);
	sprite = nullptr;
}


/* -------------------------------------------------- */
// loadd sprite
/* -------------------------------------------------- */
void Sprite::load(SDL_Renderer* renderer, const char* path) {
	sprite = IMG_LoadTexture(renderer, path);
	if (sprite == nullptr) {
		std::cout << "_texture_load_error : " << IMG_GetError() << std::endl;
		exit(-1);
	}
}