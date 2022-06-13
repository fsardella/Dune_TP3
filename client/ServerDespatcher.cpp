#include "ServerDespatcher.h"

ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    //ClientInput clientInput(std::move(blockingQueue->pop()));
}

ServerDespatcher::~ServerDespatcher() {
}