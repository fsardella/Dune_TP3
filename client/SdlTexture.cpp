#include "SdlTexture.h"
#include "Area.h"
#include <stdlib.h>
#include <string>
#include <iostream>


SdlTexture::SdlTexture(const std::string& filename, SdlWindow& window)
: window(window),
  texture(nullptr) {
	SDL_Surface* tmp = IMG_Load(filename.c_str());
	if (!tmp) {
		return;
	}

	this->texture = window.createTexture(tmp);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	width = tmp->w;
	height = tmp->h;

	SDL_FreeSurface(tmp);
}

SdlTexture::SdlTexture(const std::string &filename, SdlWindow &window, bool color)
: window(window),
  texture(nullptr) {
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        return;
    }

    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, 0, 0, 0));

    this->texture = window.createTexture(tmp);

	width = tmp->w;
	height = tmp->h;

    SDL_FreeSurface(tmp);
}

SdlTexture::SdlTexture(SdlWindow &window, TTF_Font* font, std::string text)
: window(window),
  texture(nullptr) {
    TTF_Init();
    if (font == NULL) return;

    SDL_Color textColor = {0, 0, 0, 0};

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    this->texture = window.createTexture(surface);

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
}

int SdlTexture::render(const Area& src, const Area& dest) const{
	const SDL_Rect srcRect = src.buildRectangle();
	const SDL_Rect destRect = dest.buildRectangle();
    std::cout << "entro a render de texture y ahora entraria a render de window\n";
	return window.handleRender(texture, srcRect, destRect);
}

SdlTexture::~SdlTexture() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
}

SdlTexture::SdlTexture(SdlTexture&& other) :
    window(other.window),
	texture(other.texture),
    width(other.width),
	height(other.height) 
{}
