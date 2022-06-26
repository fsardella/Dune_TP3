#include "ServerDespatcher.h"
#include <iostream>

//dispatcher*
// Por qué punteros y no referencias?
ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue<ClientInput>* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    while(true) {
        try {
            // Probablemente ya lo estén haciendo, pero acá es donde uno decidiría qué mensaje enviar.
            // Una solución es un polimorfismo
            ClientInput clientInput(std::move(blockingQueue->pop()));
            protocolClient->sendUnitConstructionPetition(clientInput.getPosX() / 4, clientInput.getPosY() / 4, 1);
        } catch (const ClosedQueueException& e) {
            return;
        } catch(const ClosedSocketException& e) {
		    std::cout << "el socket se cerro inesperadamente 1\n";
	    }
    }
}

ServerDespatcher::~ServerDespatcher() {
}