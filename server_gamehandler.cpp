#include "server_gamehandler.h"

#include <list>
#include <string>
#include <utility>
#include <stdint.h>

#ifndef CLIENTOPERS
#define CLIENTOPERS
enum clientOpers {
    XXXX = 0,
    UNIRSE,
    LISTAR,
    CREAR, // Estan en espaniol porque asi era el tp de threads. Too bad!
    DISCONNECT,
    NEW_UNIT,
    NEW_BUILDING,
    ATTACK,
    MOVE,
    ADD_BUILDING
};
#endif

GameHandler::GameHandler(Game newGame, talkerMap_t& talkerThreads):
                                        game(ActiveGame(std::move(newGame))) {
    std::list<PlayerData> playersData = this->game.getPlayersData();
    sketch_t gameMapSketch = this->game.getMapSketch();
    for (PlayerData& player : playersData) {
        this->playersQueue[player.name] = std::move(BlockingQueue<Command>());
        talkerThreads[player.name]->startPlaying(&this->commandQueue, gameMapSketch,
                                         playersData, this->playersQueue[player.name]);
    }
}

void GameHandler::processCommand(Command comm) {
    uint8_t commandType = comm.getType();
    switch (commandType) {
        case DISCONNECT:
            std::cout << "Recibi request de disconnect de " << comm.getSender() << std::endl;
            this->disconnect(comm);
            break;
        case NEW_UNIT:
            std::cout << "Recibi request de creacion de " << comm.getSender() << std::endl;
            this->addNewUnit(comm);
            break;
        case NEW_BUILDING:
            std::cout << "Recibi request de edificio de " << comm.getSender() << std::endl;
            this->createNewBuilding(comm);
            break;
        case ATTACK:
            std::cout << "Recibi request de ataque de " << comm.getSender() << std::endl;
            this->processAttack(comm);
            break;
        case MOVE:
            std::cout << "Recibi request de moverse de " << comm.getSender() << std::endl;
            this->moveUnit(comm);
            break;
        case ADD_BUILDING:
            std::cout << "Recibi request de posicionar edificio de " << comm.getSender() << std::endl;
            this->addNewBuilding(comm);
            break;
            
    }
}

void GameHandler::disconnect(Command comm) {
    this->playersQueue[comm.getSender()].close();
    this->game.disconnect(comm.getSender());
}

bool GameHandler::endedRun() {
    return this->ended;
}

void GameHandler::addNewUnit(Command comm) {
    uint8_t type = comm.pop8BytesMessage();
    this->game.addUnit(comm.getSender(), type);
}

void GameHandler::createNewBuilding(Command comm) {
    uint8_t type = comm.pop8BytesMessage();
    this->game.createBuilding(comm.getSender(), type);  
}

void GameHandler::addNewBuilding(Command comm) {
    uint16_t x = comm.pop16BytesMessage();
    uint16_t y = comm.pop16BytesMessage();
    bool result = this->game.addBuilding(comm.getSender(), x, y);
    if (!result)
        this->notifyError(comm);
    else
        this->notifySuccess(comm);
}

#define ATTACK_UNIT 0
#define ATTACK_BUILDING 1

void GameHandler::processAttack(Command comm) {
    uint8_t type = comm.pop8BytesMessage();
    uint16_t attacker = comm.pop16BytesMessage();
    uint16_t attacked = comm.pop16BytesMessage();
    switch (type) {
        case ATTACK_UNIT:
            this->game.attackUnit(attacker, attacked);
            break;
        case ATTACK_BUILDING:
            this->game.attackBuilding(attacker, attacked);
            break;
    }
}

void GameHandler::moveUnit(Command comm) {
    uint16_t unitID = comm.pop16BytesMessage();
    uint16_t x = comm.pop16BytesMessage();
    uint16_t y = comm.pop16BytesMessage();
    this->game.moveUnit(comm.getSender(), unitID, x, y);
    
}

#include <iostream> // DEBUG DEBUG DEBUGDEBUG DEBUG DEBUGDEBUG DEBUG DEBUGDEBUG DEBUG DEBUG

#define SUCCESS 0
#define FAILURE 1

void GameHandler::notifyError(Command comm) {
    Command errorCom;
    errorCom.setType(FAILURE);
    errorCom.add8BytesMessage(FAILURE);
    errorCom.changeSender(comm.getSender());
    this->playersQueue[errorCom.getSender()].push(errorCom);
}

void GameHandler::notifySuccess(Command comm) {
    Command succCom;
    succCom.setType(SUCCESS);
    succCom.add8BytesMessage(SUCCESS);
    succCom.changeSender(comm.getSender());
    this->playersQueue[succCom.getSender()].push(succCom);
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
