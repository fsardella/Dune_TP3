#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
	

#include "server_listener.h"
#include "server_talker.h"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor del escuchador de Clientes.
*/

Listener::Listener(const char* service_port, GameSet *gameSet,
    talkerMap_t& clientTalkers, Config* c): c(c),
                                                  socket_original(service_port),
                                                  clientTalkers(clientTalkers),
                                                  listening(true) {
    this->gameSet = gameSet;
}

/*
Pre-Condiciones: -
Post-Condiciones: El escuchador de Clientes aceptará conexiones entrantes. Cada vez que 
recibe una conexión nueva se instancia un hilo nuevo para el cliente 
(seria el Hablador de Clientes) y cada uno de ellos se va a agregar a la lista con todos los
clientes aceptados.
*/

void Listener::run() {
	while(true) {
		try {
			Socket accept = this->socket_original.accept();
			Talker *client_talker = new Talker(std::move(accept), gameSet, c);
			clientTalkers[client_talker->getPlayerName()] = client_talker;
			client_talker->start();
			cleanFinishedHandlers();
		} catch (ClosedSocketException const&) {
            std::cout << "Stopped accepting players" << std::endl;
			break;
		} catch (std::runtime_error const& e) {
            if (std::string(e.what()) == "Socket disconnected before creation")
                continue;
            throw;
        }
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Limpia el contenedor de hilos manejadores a medida que estos van terminando,
para que no se vayan acumulando.
*/

void Listener::cleanFinishedHandlers() {
    talkerMap_t::iterator it = clientTalkers.begin();
    while (it != clientTalkers.end()) {
        if ((it->second)->finishedThread()) {
            delete it->second;
            it = clientTalkers.erase(it);
        } else {
            ++it;
        }
    }
}

void Listener::stopListening() {
    this->socket_original.closeSkt();
    this->listening = false;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del escuchador de Clientes.
*/
Listener::~Listener() {
	if (this->listening)
        this->socket_original.closeSkt();
    for (auto& c:clientTalkers) {
		delete c.second;
	}
	this->join();
}
