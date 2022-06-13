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

Server::Server(const char* service_port): gameSet(), listener(service_port, &gameSet) {
	this->listener.start();
}

/*
Pre-Condiciones: Se instancia a la clase Servidor.
Post-Condiciones: Hilo principal (en el main). Se queda esperando que se reciba algo por
entrada estándar. Si se recibe una "q" el Servidor finalizará.
*/

void Server::server_run() {
	std::string input;
	while (input != "q") {
		std::cin >> input;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del Servidor.
*/

Server::~Server() {
}
