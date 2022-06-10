#include "SdlTexture.h"
#include "Area.h"


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

int SdlTexture::render(const Area& src, const Area& dest) const{
	const SDL_Rect srcRect = src.buildRectangle();
	const SDL_Rect destRect = dest.buildRectangle();
	return window.handleRender(texture, srcRect, destRect);
} 


SdlTexture::~SdlTexture() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
}
