#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "SdlWindow.h"
#include "Area.h"

class SdlTexture {
	SdlWindow& window;
	SDL_Texture* texture;

	int width;
	int height;

    public:
	SdlTexture(const std::string& filename, SdlWindow& window);
    SdlTexture(const std::string& filename,
               SdlWindow& window,bool color);

    SdlTexture(const SdlTexture& other) = delete;
    SdlTexture& operator=(const SdlTexture& other) = delete;

    SdlTexture(SdlTexture&& other) ;
    SdlTexture& operator=(SdlTexture&& other) ;

    int render(const Area& src, const Area& dest) const;

	~SdlTexture();
};

#endif
