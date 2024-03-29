#ifndef SDLTEXTURE_H
#define SDLTEXTURE_H

#include "SdlWindow.h"
#include "Area.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class SdlTexture {
    SdlWindow* window;
    SDL_Texture* texture;

    int width;
    int height;

 public:
    SdlTexture(SdlWindow* window, TTF_Font* font, std::string text);
    SdlTexture(const std::string& filename, SdlWindow* window);
    SdlTexture(const std::string& filename, SdlWindow* window,
               int r, int g, int b);
    SdlTexture(const std::string &filename,
                           SdlWindow* window, SDL_BlendMode blending,
                           uint8_t alpha);

    SdlTexture(const SdlTexture& other) = delete;
    SdlTexture& operator=(const SdlTexture& other) = delete;

    SdlTexture(SdlTexture&& other);
    SdlTexture& operator=(SdlTexture&& other);

    int render(const Area& src, const Area& dest) const;

    ~SdlTexture();
};

#endif
