#include "ServerDespatcher.h"
#include <iostream>

#define CREATE_UNIT 5
#define CREATE_BUILDING 6
#define ATTACK 7

ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue<ClientInput>* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    while(true) {
        try {
            ClientInput clientInput(std::move(blockingQueue->pop()));
            int operation = clientInput.getOperation();
            if (operation != ATTACK) {
                protocolClient->sendConstructionPetition(operation, clientInput.getType());
            } else {
                protocolClient->sendOperationInfo(operation, clientInput.getType(),
                                                  clientInput.getParam1(), clientInput.getParam2());
            }
        } catch (const ClosedQueueException& e) {
            return;
        } catch(const ClosedSocketException& e) {
            std::cout << "el socket se cerro inesperadamente 1\n";
        }
    }
}

ServerDespatcher::~ServerDespatcher() {
}