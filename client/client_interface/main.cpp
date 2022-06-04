#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL.h>
#include <SDL_image.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[])
{
    try {
        // Clase que contiene el loop principal
        QApplication app(argc, argv);
        // Instancio la ventana principal
        Client client;
        MainWindow window(NULL, &client);
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
        //std::cout << "el numero de casa es: " << client.houseNumber;
        //std::cout << "el nombre del juego es" << client.game_name;
        //std::cout << "el mapa del juego es" << client.map_name;

        //The window we'll be rendering to
        SDL_Window* sdl_window = NULL;

        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;

        //Initialize SDL
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Create window
            sdl_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
            if( sdl_window == NULL )
            {
                printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Get window surface
                screenSurface = SDL_GetWindowSurface( sdl_window );

                //Fill the surface white
                SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

                //Update the surface
                SDL_UpdateWindowSurface( sdl_window );

                //Wait two seconds
                SDL_Delay( 2000 );
            }
        }

        //Destroy window
        SDL_DestroyWindow( sdl_window );

        //Quit SDL subsystems
        SDL_Quit();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
    return 0;
}
