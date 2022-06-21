#include "ServerDespatcher.h"
#include <iostream>

ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue<ClientInput>* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    while(true) {
        try {
            ClientInput clientInput(std::move(blockingQueue->pop()));
            protocolClient->sendUnitConstructionPetition(clientInput.getPosX() / 4, clientInput.getPosY() / 4, 1);
        } catch (const ClosedQueueException& e) {
            std::cout << "la cola se cerro inesperadamente 1\n";
            return;
        } catch(const ClosedSocketException& e) {
		    std::cout << "el socket se cerro inesperadamente 1\n";
	    }
    }
}

ServerDespatcher::~ServerDespatcher() {
}