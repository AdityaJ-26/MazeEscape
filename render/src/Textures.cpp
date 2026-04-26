#include <iostream>

#include "Textures.h"

/* -------------------------------------------------- */
// consturctor / desturctor
/* -------------------------------------------------- */
Texture::Texture() :
	tex(nullptr)
{ }

Texture::~Texture() {
	SDL_DestroyTexture(tex);
	tex = nullptr;
}


/* -------------------------------------------------- */
// load texture
/* -------------------------------------------------- */
void Texture::load(SDL_Renderer* renderer, const char* path) {
	tex = IMG_LoadTexture(renderer, path);

	if (tex == nullptr) {
		std::cerr << "_texture_load_error : " << IMG_GetError() << std::endl;
		exit(-1);
	}
}