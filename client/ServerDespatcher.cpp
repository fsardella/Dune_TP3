#include "ServerDespatcher.h"
#include <iostream>

ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    //esto lo comente porque generaba el loop y la ventana no se cerraba nunca. Posiblemente sea porque no tiene nada para popear
    ClientInput clientInput(std::move(blockingQueue->pop())); 
    std::cout << clientInput.getPosX() << " " << clientInput.getPosY();
    // protocolClient->sendUnitConstructionPetition(clientInput.getX(), clientInput.getY(), 1);
}

ServerDespatcher::~ServerDespatcher() {
}