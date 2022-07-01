#include "ServerDespatcher.h"
#include <iostream>

#define CREATE_UNIT 5
#define CREATE_BUILDING 6
#define ATTACK 7
#define MOVEMENT 8
#define POSITION_BUILDING 9
#define CHASE 10
#define DESTRUCTION 11

ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue<ClientInput>* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    while(true) {
        try {
            ClientInput clientInput(std::move(blockingQueue->pop()));
            int operation = clientInput.getOperation();
            switch (operation)
		    {
            case CREATE_UNIT:
                protocolClient->sendConstructionPetition(operation, clientInput.getParam1());
                break;
            case CREATE_BUILDING:
                protocolClient->sendConstructionPetition(operation, clientInput.getParam1());
                break;
            case ATTACK:
                protocolClient->sendAttacknInfo(operation, clientInput.getParam1(),
                                                clientInput.getParam2(), clientInput.getParam3());
                break;
            case MOVEMENT:
                protocolClient->sendMovementUnit(operation, clientInput.getParam1(),
                                                 clientInput.getParam2(), clientInput.getParam3());
                break;
            case POSITION_BUILDING:
                protocolClient->sendBuildingPosition(operation, clientInput.getParam1(),
                                                     clientInput.getParam2());
                break;
            case CHASE:
                protocolClient->sendChasingInfo(operation, clientInput.getParam1(),
                                                clientInput.getParam2());
                break;
            case DESTRUCTION:
                protocolClient->sendBuildingDestruction(operation, clientInput.getParam1());
                break;
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