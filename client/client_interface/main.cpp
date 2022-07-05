#include <QApplication>
#include <SDL2pp/SDL2pp.hh>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "mainwindow.h"
#include "winwindow.h"
#include "losewindow.h"

#define MASK 255, 255, 255

int main(int argc, char *argv[]) {
    try {
        QApplication app(argc, argv);
        Client client;
        MainWindow window(NULL, &client);
        window.showMaximized();

        if (app.exec()) {
            throw std::runtime_error(
                "La aplicación QT finalizó de forma incorrecta");
        }
        if (client.isReadyToRun()) {
            client.client_run();
        }

        // qt
        if (client.getGameResult() == 1) {
            WinWindow winWindow(NULL);
            winWindow.showMaximized();
            if (app.exec()) {
                throw std::runtime_error(
                    "La aplicación QT finalizó de forma incorrecta");
            }
        }
        if (client.getGameResult() == 0) {
            LoseWindow loseWindow(NULL);
            loseWindow.showMaximized();
            if (app.exec()) {
                throw std::runtime_error(
                    "La aplicación QT finalizó de forma incorrecta");
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido en la función main" << std::endl;
    }
    return 0;
}
