#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "SdlWindow.h"


SdlWindow::SdlWindow(int width, int height, bool fullScreen, std::string title) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED, &this->windowPtr, &this->rendererPtr);
	SDL_SetWindowTitle(this->windowPtr, title.c_str());
	if (fullScreen) {
		SDL_SetWindowFullscreen(this->windowPtr, SDL_WINDOW_FULLSCREEN);
	}
	this->width = width;
    this->height = height;
}

void SdlWindow::setSize(int newWidth, int newHeight) {
	this->width = newWidth;
	this->height = newHeight;
	SDL_SetWindowSize(windowPtr, width, height);
}

void SdlWindow::fill(uint8_t redValue, uint8_t greenValue, uint8_t blueValue, int alphaValue) {
	SDL_SetRenderDrawColor(rendererPtr, redValue, greenValue, blueValue, alphaValue);
	SDL_RenderClear(rendererPtr);
}

SDL_Texture* SdlWindow::createTexture(SDL_Surface* aSurface) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rendererPtr, aSurface);
	return texture;
}

void SdlWindow::render() {
	SDL_RenderPresent(rendererPtr);
}

int SdlWindow::handleRender(SDL_Texture* txt, const SDL_Rect& src, const SDL_Rect& dst) {
	return SDL_RenderCopy(rendererPtr, txt, &src, &dst);
}

SDL_Point SdlWindow::getCenter() {
	SDL_Point p;
	SDL_GetWindowSize(windowPtr, &p.x, &p.y);
	p.x /= 2;
	p.y /= 2;
	return p;
}

int SdlWindow::handleRender(SDL_Texture *txt, const SDL_Rect &src, const SDL_Rect &dst, float ang, SDL_Point &center,
                            SDL_RendererFlip flip) {
    return SDL_RenderCopyEx(rendererPtr, txt, &src, &dst, ang, &center, flip);
}

int SdlWindow::handleRender(SDL_Texture *txt, const SDL_Rect &src, const SDL_Rect &dst, uint8_t alpha) {
    SDL_SetTextureAlphaMod(txt, alpha);
    return SDL_RenderCopyEx(rendererPtr, txt, &src, &dst, 0, nullptr, SDL_FLIP_NONE);
}

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