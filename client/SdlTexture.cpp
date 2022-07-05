#include "SdlTexture.h"
#include "Area.h"
#include <stdlib.h>
#include <string>

#define BLACK 0
#define ALPHA 0

/*
Pre-Condiciones: Constructor de la clase SdlTexture a partir de un
path a una imagen y un puntero a una ventana.
Post-Condiciones: -
*/

SdlTexture::SdlTexture(const std::string& filename, SdlWindow* window)
: window(window),
  texture(nullptr) {
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        return;
    }

    this->texture = window->createTexture(tmp);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    width = tmp->w;
    height = tmp->h;

    SDL_FreeSurface(tmp);
}

/*
Pre-Condiciones: Constructor de la clase SdlTexture a partir de un
path a una imagen, un puntero a una ventana y un color en formato
RGB para filtrar de la imagen.
Post-Condiciones: -
*/

SdlTexture::SdlTexture(const std::string &filename,
                       SdlWindow* window, int r, int g, int b)
: window(window),
  texture(nullptr) {
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        return;
    }

    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, r, g, b));

    this->texture = window->createTexture(tmp);

    width = tmp->w;
    height = tmp->h;

    SDL_FreeSurface(tmp);
}

/*
Pre-Condiciones: Constructor de la clase SdlTexture a partir de un
path a una imagen, un puntero a una ventana, un modo y
un alpha de opacidad.
Post-Condiciones: -
*/

SdlTexture::SdlTexture(const std::string &filename, SdlWindow* window,
                       SDL_BlendMode blending, uint8_t alpha)
: window(window),
  texture(nullptr) {
    SDL_Surface* tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        return;
    }

    this->texture = window->createTexture(tmp);

    SDL_SetTextureBlendMode(this->texture, blending);
    SDL_SetTextureAlphaMod(this->texture, alpha);

    width = tmp->w;
    height = tmp->h;

    SDL_FreeSurface(tmp);
}

/*
Pre-Condiciones: Constructor de la clase SdlTexture a partir de un
puntero a una ventana, una font de letra y un texto.
Post-Condiciones: -
*/

SdlTexture::SdlTexture(SdlWindow* window, TTF_Font* font, std::string text)
: window(window),
  texture(nullptr) {
    TTF_Init();
    if (font == NULL) return;

    SDL_Color textColor = {BLACK, BLACK, BLACK, ALPHA};

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

    this->texture = window->createTexture(surface);

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
}

/*
Pre-Condiciones: Renderiza la textura en la ventana.
Post-Condiciones: -
*/

int SdlTexture::render(const Area& src, const Area& dest) const {
    const SDL_Rect srcRect = src.buildRectangle();
    const SDL_Rect destRect = dest.buildRectangle();
    return window->handleRender(texture, srcRect, destRect);
}

/*
Pre-Condiciones: Destructor de la clase SdlTexture.
Post-Condiciones: -
*/

SdlTexture::~SdlTexture() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
}

/*
Pre-Condiciones: Constructor por movimiento de la clase SdlTexture.
Post-Condiciones: -
*/

SdlTexture::SdlTexture(SdlTexture&& other) :
    window(other.window),
    texture(other.texture),
    width(other.width),
    height(other.height)
{}
