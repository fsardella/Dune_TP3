#include <SDL2pp/SDL2pp.hh>
#include "Gameloop.h"

int main(int argc, char** argv){
    try {
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        SDL2pp::Window sdlWindow("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 800, 600,
                                 SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(sdlWindow, -1, SDL_RENDERER_SOFTWARE);

        // Encapsular en un repositorio de texturas para no crear multiples veces la misma textura
        SDL2pp::Texture im(renderer,
                           SDL2pp::Surface("assets/soldier2.png").SetColorKey(true, 0));

        Gameloop gameloop(renderer, im);
        gameloop.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }

}
