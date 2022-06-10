#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_mixer.h>

class SdlWindow {
	int width;
	int height;
	SDL_Window* windowPtr;
	SDL_Renderer* rendererPtr;

	public:
	SdlWindow(int width, int height, bool fullScreen, std::string title);

	SdlWindow(const SdlWindow& other) = delete;
	SdlWindow& operator=(const SdlWindow& other) = delete;

	void fill(uint8_t redValue, uint8_t greenValue, uint8_t blueValue, int alphaValue);
	void render();

	SDL_Texture* createTexture(SDL_Surface* aSurface);
	int handleRender(SDL_Texture* txt, const SDL_Rect& src, const SDL_Rect& dst);

    int handleRender(SDL_Texture* txt, const SDL_Rect& src,
                     const SDL_Rect& dst, float ang,
                     SDL_Point& center,
                     SDL_RendererFlip flip);

    int handleRender(SDL_Texture* txt,
                     const SDL_Rect& src,
                     const SDL_Rect& dst,
                     uint8_t alpha);

	SDL_Point getCenter();

	~SdlWindow();
};

#endif