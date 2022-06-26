#include "server_gamehandler.h"

#include <list>
#include <string>
#include <utility>
#include <stdint.h>

#define DISCONNECT 4
#define NEW_UNIT 5

GameHandler::GameHandler(Game newGame, talkerMap_t& talkerThreads):
                                        game(ActiveGame(std::move(newGame))) {
    std::list<std::string> names = this->game.getPlayerNames();
    sketch_t gameMapSketch = this->game.getMapSketch();
    for (std::string name : names) {
        this->playersQueue[name] = std::move(BlockingQueue<Command>());
        talkerThreads[name]->startPlaying(&this->commandQueue, gameMapSketch,
                                         this->playersQueue[name]);
    }
}

void GameHandler::processCommand(Command comm) {
    uint8_t commandType = comm.getType();
    switch (commandType) { // Posible diccionario!
        case DISCONNECT:
            std::cout << "Recibi request de disconnect de " << comm.getSender() << std::endl;
            this->disconnect(comm);
            break;
        case NEW_UNIT:
            std::cout << "Recibi request de creacion de " << comm.getSender() << std::endl;
            this->addNewUnit(comm);
            break;
    }
}

void GameHandler::disconnect(Command comm) {
    this->playersQueue[comm.getSender()].close();
}

bool GameHandler::endedRun() {
    return this->ended;
}

void GameHandler::addNewUnit(Command comm) {
    int x = (int) comm.pop16BytesMessage();
    int y = (int) comm.pop16BytesMessage();
    // TODO TRADUCIR EL TYPE
    bool result = this->game.addUnit(comm.getSender(), x, y);
    if (!result)
        this->notifyError(comm);
    else
        this->notifySuccess(comm);
}

#include <iostream> // DEBUG DEBUG DEBUGDEBUG DEBUG DEBUGDEBUG DEBUG DEBUGDEBUG DEBUG DEBUG

void GameHandler::notifyError(Command comm) {
    Command errorCom;
    errorCom.setType(69);
    errorCom.changeSender(comm.getSender());
    std::cout << "Error por parte de " << errorCom.getSender() << std::endl;
}

void GameHandler::notifySuccess(Command comm) {
    Command succCom;
    succCom.setType(68);
    succCom.changeSender(comm.getSender());
    std::cout << "Accion realizada por parte de " << succCom.getSender() << std::endl;
}

void GameHandler::run() {
    Command comm;
    Broadcaster broad(this->game, this->playersQueue, this->commandQueue);
    broad.start();
    TimeWizard wizard(this->game);
    wizard.start();
    try {
        while (this->game.isAlive()) {
            comm = commandQueue.pop();
            this->processCommand(comm);
        }
    } catch(const ClosedQueueException& e) {
    }
    this->ended = true;
}
    
GameHandler::~GameHandler() {
    this->join();
}
