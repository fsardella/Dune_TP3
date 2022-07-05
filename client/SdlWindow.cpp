#include "SdlWindow.h"
#include <SDL2/SDL_ttf.h>

#define MENUOFFSET 50
#define SPACINGX 20
#define SPACINGY 20
#define FRECUENCY 44100
#define CHANNELS 2
#define CHUNK_SIZE 4096
#define POS_X 70
#define POS_Y 0

/*
Pre-Condiciones: Constructor de window.
Post-Condiciones: -
*/

SdlWindow::SdlWindow(int width, int height, bool fullScreen,
                     std::string title): sounds() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                &this->windowPtr, &this->rendererPtr);
    SDL_SetWindowPosition(this->windowPtr, POS_X, POS_Y);
    SDL_SetWindowTitle(this->windowPtr, title.c_str());
    if (fullScreen) {
        SDL_SetWindowFullscreen(this->windowPtr, SDL_WINDOW_FULLSCREEN);
    }
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(FRECUENCY, MIX_DEFAULT_FORMAT, CHANNELS, CHUNK_SIZE);
    sounds.loadSounds();
    sounds.playSounds();
    this->width = width;
    this->height = height;
}

/*
Pre-Condiciones: Setea el tamaño de la window.
Post-Condiciones: -
*/

void SdlWindow::setSize(int newWidth, int newHeight) {
    this->width = newWidth;
    this->height = newHeight;
    SDL_SetWindowSize(windowPtr, width, height);
}

/*
Pre-Condiciones: Setea el color de la window.
Post-Condiciones: -
*/

void SdlWindow::fill(uint8_t redValue, uint8_t greenValue, uint8_t blueValue,
                    int alphaValue) {
    SDL_SetRenderDrawColor(rendererPtr, redValue, greenValue, blueValue,
                           alphaValue);
    SDL_RenderClear(rendererPtr);
}

/*
Pre-Condiciones: Crea una textura.
Post-Condiciones: -
*/

SDL_Texture* SdlWindow::createTexture(SDL_Surface* aSurface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendererPtr, aSurface);
    return texture;
}

/*
Pre-Condiciones: Renderiza la window.
Post-Condiciones: -
*/

void SdlWindow::render() {
    SDL_RenderPresent(rendererPtr);
}

/*
Pre-Condiciones: Renderiza un rectángulo.
Post-Condiciones: -
*/

void SdlWindow::renderRect(SDL_Rect& r) {
    SDL_RenderFillRect(rendererPtr, &r);
}

/*
Pre-Condiciones: Rederiza una textura.
Post-Condiciones: -
*/

int SdlWindow::handleRender(SDL_Texture* txt, const SDL_Rect& src,
                            const SDL_Rect& dst) {
    return SDL_RenderCopy(rendererPtr, txt, &src, &dst);
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el centro de la window.
*/

SDL_Point SdlWindow::getCenter() {
    SDL_Point p;
    SDL_GetWindowSize(windowPtr, &p.x, &p.y);
    p.x /= 2;
    p.y /= 2;
    return p;
}

/*
Pre-Condiciones: Se pushea en un vector de reproducibles los sonidos que
actualmente se quieren reproducir en el juego y se reproducen.
Post-Condiciones: -
*/

void SdlWindow::playSounds() {
    sounds.playSounds();
}

/*
Pre-Condiciones: Se pushea en un vector de reproducibles los sonidos que
actualmente se quieren reproducir en el juego.
Post-Condiciones: -
*/

void SdlWindow::push(int soundId, int volume) {
    sounds.push(soundId, volume);
}

/*
Pre-Condiciones: Destructor de window.
Post-Condiciones: -
*/

SdlWindow::~SdlWindow() {
    if (this->rendererPtr) {
        SDL_DestroyRenderer(this->rendererPtr);
        rendererPtr = nullptr;
    }
    if (this->windowPtr) {
        SDL_DestroyWindow(this->windowPtr);
        windowPtr = nullptr;
    }
    SDL_Quit();
}
