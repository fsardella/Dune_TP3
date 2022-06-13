#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <utility>

#include "server_listener.h"
#include "server_talker.h"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor del escuchador de Clientes.
*/

Listener::Listener(const char* service_port, GameSet *gameSet): socket_original(service_port) {
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
			Talker *client_talker = new Talker(std::move(accept), gameSet);
			clientsTalkers.push_back(client_talker);
			client_talker->start();
			cleanFinishedHandlers();
		}
		catch (ClosedSocketException const&) {
			break;
		}
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Limpia el contenedor de hilos manejadores a medida que estos van terminando,
para que no se vayan acumulando.
*/

void Listener::cleanFinishedHandlers() {
    std::list<Talker *>::iterator it = clientsTalkers.begin();
    while (it != clientsTalkers.end()) {
        if ((*it)->finishedThread()) {
            delete *it;
            it = clientsTalkers.erase(it);
        } else {
            ++it;
        }
    }
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del escuchador de Clientes.
*/

Listener::~Listener() {
	for (Talker* c:clientsTalkers) {
		delete c;
	}
	this->socket_original.closeSkt();
	this->join();
}
