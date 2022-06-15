#include "ServerDespatcher.h"
#include <iostream>

ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue<ClientInput>* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    try {
        ClientInput clientInput(std::move(blockingQueue->pop())); 
        std::cout << clientInput.getPosX() << " " << clientInput.getPosY();
        // protocolClient->sendUnitConstructionPetition(clientInput.getX(), clientInput.getY(), 1);
    } catch (ClosedQueueException& e) {
        return;
    }
}

ServerDespatcher::~ServerDespatcher() {
}