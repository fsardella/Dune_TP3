#include "client_client.h"
#include <arpa/inet.h>
#include "ClientInput.h"
#include "Drawer.h"
#include "MapView.h"
#include "UserInputReceiver.h"
#include "BlockingQueue.h"
#include "ServerDispatcher.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <cstring>

#define HARKONNEN 0
#define ATREIDES 1
#define ORDOS 2
#define WINDOW_HEIGHT 700
#define WINDOW_WIDHT 1300
#define BROWN_COLOR_R 192
#define BROWN_COLOR_G 150
#define BROWN_COLOR_B 100
#define ALPHA 255
#define GAME_NAME "DUNE 2000"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Cliente.
*/

Client::Client()
: readyToRun(false),
  houseNumber(0),
  gameResult(-1),
  protocol() {
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
Post-Condiciones: Se determina el nombre del jugador.
*/

void Client::chooseName(std::string name) {
    this->name = name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina el numero de la casa elegida por el Cliente segun
el nombre de la casa.
*/

void Client::chooseNumberHouse(std::string house) {
    if ((house.compare(HOUSE_HARKONNEN)) == 0) {
        this->houseNumber = HARKONNEN;
    } else if ((house.compare(HOUSE_ATREIDES)) == 0) {
        this->houseNumber = ATREIDES;
    } else if ((house.compare(HOUSE_ORDOS)) == 0) {
        this->houseNumber = ORDOS;
    } else {
        throw std::invalid_argument("House not valid");
    }
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina el nombre del juego elegido por el Cliente.
*/

void Client::chooseGameName(std::string name) {
    this->gameName = name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina el nombre del mapa elegido por el Cliente.
*/

void Client::chooseMapName(std::string name) {
    this->mapName = name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Se lanza al cliente.
*/

void Client::client_run() {
    SdlWindow sdlWindow(WINDOW_WIDHT, WINDOW_HEIGHT, false, GAME_NAME);
    sdlWindow.fill(BROWN_COLOR_R, BROWN_COLOR_G, BROWN_COLOR_B, ALPHA);
    GameView gameViewObj(sdlWindow, houseNumber);

    int result = -1;
    ServerReceiver receiver(&protocol, &gameViewObj, name, result);
    receiver.start();

    Drawer drawer(&gameViewObj);
    drawer.start();

    BlockingQueue<ClientInput> blockingQueue;
    UserInputReceiver inputReceiver(&gameViewObj, &blockingQueue);
    inputReceiver.start();

    ServerDispatcher serverDispatcher(&protocol, &blockingQueue);
    serverDispatcher.start();

    drawer.join();
    inputReceiver.join();
    serverDispatcher.join();
    receiver.join();

    gameResult = result;
    
}

/*
Pre-Condiciones: -
Post-Condiciones: Se obtiene el resultado del juego para un jugador.
*/

int Client::getGameResult() {
    return gameResult;
}

/*
Pre-Condiciones: -
Post-Condiciones: Se obtiene el nombre del jugador.
*/

void Client::sendUserName() {
    protocol.sendUserName(name);
}

/*
Pre-Condiciones: Se envía la operación de crear juego.
Post-Condiciones: -
*/

void Client::sendCreateGameOperation() {
    protocol.sendCreateGameOperation(CREATE_GAME);
}

/*
Pre-Condiciones: Se envía la informacón para crear el juego.
Post-Condiciones: -
*/

void Client::sendCreateGameInfo() {
    protocol.sendCreateGameInfo(gameName, mapName, houseNumber);
}

/*
Pre-Condiciones: Se envía la operación para unirse a un juego.
Post-Condiciones: -
*/

void Client::sendJoinGameOperation() {
    protocol.sendJoinGameOperation(JOIN_GAME, gameName, houseNumber);
}

/*
Pre-Condiciones: Se envía la operación para listar juegos.
Post-Condiciones: -
*/

void Client::sendListGamesOperation() {
    protocol.sendListGamesOperation(LIST_GAMES);
}

/*
Pre-Condiciones: Se envía la operación para listar mapas.
Post-Condiciones: -
*/

void Client::sendListMapsOperation() {
    // protocol.sendListMapsOperation(LIST_MAPS);
}

/*
Pre-Condiciones: Se recibe la lista de mapas.
Post-Condiciones: -
*/

void Client::recvListOfMaps(std::list<std::string>& list) {
    protocol.recvListOfMaps(list);
}

/*
Pre-Condiciones: Se recibe la lista de juegos.
Post-Condiciones: -
*/

void Client::recvListOfGames(std::list<std::string>& list) {
    protocol.recvListOfGames(list);
}


/*
Pre-Condiciones: Se recibe la operación de empezar juego.
Post-Condiciones: -
*/

int Client::recvStartGame() {
    return protocol.recvStartGame();
}

/*
Pre-Condiciones: Se recibe el resultado de la operación.
Post-Condiciones: -
*/

int Client::recvOperationResult() {
    return protocol.recvOperationResult();
}

/*
Pre-Condiciones: -
Post-Condiciones: Se setea en true que el cliente esta listo para comenzar
la partida.
*/

void Client::setReadyToRun() {
    readyToRun = true;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el cliente esta listo para comenzar la partida
o false si no. 
*/

bool Client::isReadyToRun() {
    return readyToRun;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del cliente.
*/

Client::~Client() {
}
