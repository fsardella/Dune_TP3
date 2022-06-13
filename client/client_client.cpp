#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <arpa/inet.h>
#include <vector>
#include <fstream>
#include <cstring>

#include "client_client.h"
#include "Drawer.h"
#include "MapView.h"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Cliente.
*/
/*
Client::Client(YAML::Node& configuration):protocol(),clientConfiguration(configuration),sdlWindow(clientConfiguration["width"].as<int>(),
    clientConfiguration["height"].as<int>(),
    clientConfiguration["fullscreen"].as<bool>(), "DUNE 2000") {
}
*/

Client::Client():protocol() {
}
/*
Pre-Condiciones: -
Post-Condiciones: El cliente se conecta a un servidor.
*/

void Client::setConnection(const char* name_host, const char* service_port) {
	this->protocol.setSktConnection(name_host, service_port);
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina el numero de la casa elegida por el Cliente segun el nombre de la casa.
*/

void Client::chooseNumberHouse(std::string house) {
	if ((house.compare(HOUSE_HARKONNEN)) == 0) {
		this->houseNumber = 0;
	} else if ((house.compare(HOUSE_ATREIDES)) == 0) {
		this->houseNumber = 1;
	} else if ((house.compare(HOUSE_ORDOS)) == 0) {
		this->houseNumber = 2;
	} else {
		throw std::invalid_argument("House not valid");
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina el nombre del juego elegido por el Cliente.
*/


void Client::chooseGameName(std::string name) {
	this->game_name = name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina el nombre del mapa elegido por el Cliente.
*/

void Client::chooseMapName(std::string name) {
	this->map_name = name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Se lanza al cliente.
*/

void Client::client_run() {

	int height = 600;
	int width = 800;
	SdlWindow sdlWindow(width, height, false, "DUNE 2000");
	GameView gameViewObj(sdlWindow);

	ServerReceiver receiver(&protocol, &gameViewObj);
	receiver.start();

	Drawer drawer(&gameViewObj);
	drawer.start();

	drawer.join();
	receiver.join();
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del cliente.
*/

Client::~Client() {
}
