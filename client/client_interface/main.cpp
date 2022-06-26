#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include <SDL2pp/SDL2pp.hh>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#define MASK 255, 255, 255

<<<<<<< HEAD
#define CLIENT_CONFIG "../client_config.yaml"

int main(int argc, char *argv[])
{
    YAML::Node clientConfig;

    try {
        clientConfig = YAML::LoadFile(CLIENT_CONFIG);
    } catch(const std::exception& e) {
        std::cout << e.what();
        return -1;
    }
=======
int main(int argc, char *argv[])
{
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
    try {
        // Clase que contiene el loop principal
        QApplication app(argc, argv);
        // Instancio la ventana principal
<<<<<<< HEAD
        //Client client(clientConfig);
=======
>>>>>>> 36cfca8b5fc3e40013363ce7346d4da70ed724dd
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
        client.client_run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
    return 0;
}
