#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <utility>
#include <string>

#include "server_server.h"
#include "server_listener.h"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Servidor.
*/

Server::Server(Config* c): c(c),
                           gameSet(this->playableGames),
                           talkers(),
                           activeGames(),
                           listener(c->PORT.c_str(), &gameSet,
                                    this->talkers, c),
                           inputGuy(this->listener,
                                    this->playableGames) {
	this->listener.start();
}

/*
Pre-Condiciones: Se instancia a la clase Servidor.
Post-Condiciones: Hilo principal (en el main). Se queda esperando que se reciba algo por
entrada estándar. Si se recibe una "q" el Servidor finalizará.
*/

void Server::cleanGames() {
    std::list<GameHandler*>::iterator iter = this->activeGames.begin();
    while (iter != this->activeGames.end()) {
        if ((*iter)->endedRun()) {
            delete *iter;
            iter = this->activeGames.erase(iter);
        } else {
            ++iter;
        }
    }
}

void Server::server_run() {
    this->inputGuy.start();
    try {
        while(true) {
            Game newGame = std::move(this->playableGames.pop());
            std::cout << "Comenzando Game " << newGame.get_name() << "..." << std::endl;
            GameHandler* newGameThread = new GameHandler(std::move(newGame), this->talkers, c);
            newGameThread->start();
            this->activeGames.push_back(newGameThread);
            this->cleanGames();
        }
    } catch (const ClosedQueueException&) {
        return;
    }
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del Servidor.
*/

Server::~Server() {
    for (GameHandler* th : this->activeGames)
        delete th;
}
