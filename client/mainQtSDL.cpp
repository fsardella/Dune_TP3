#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "Gameloop.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL.h>
#include <SDL_image.h>


int main(int argc, char *argv[]) {
    try {
        // Clase que contiene el loop principal
        QApplication app(argc, argv);
        // Instancio la ventana principal
        MainWindow window;
        window.showMaximized();
        /*
         * QApplication::exec inicia el event loop y se queda esperando que finalice la aplicación. Cuando el usuario
         * realice una acción que haga un exit de QT, entonces esta función retorna (con el código de error
         * si lo hubo) y entonces se podrá crear la ventana de SDL.
         */
        // exec es una función bloqueante, cuando QT finaliza su ejecución, se realiza un return con el codigo de error
        if (app.exec()) {
            throw std::runtime_error("La aplicación QT finalizó de forma incorrecta");
        }


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
    return 0;
}
