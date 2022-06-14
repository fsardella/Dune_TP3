#include "ServerDespatcher.h"

ServerDespatcher::ServerDespatcher(ProtocolClient* protocol, BlockingQueue* blockingQueue): 
protocolClient(protocol), blockingQueue(blockingQueue) {
}

void ServerDespatcher::run() {
    //esto lo comente porque generaba el loop y la ventana no se cerraba nunca. Posiblemente sea porque no tiene nada para popear
    //ClientInput clientInput(std::move(blockingQueue->pop())); 
}

ServerDespatcher::~ServerDespatcher() {
}