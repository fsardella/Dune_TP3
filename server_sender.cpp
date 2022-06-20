#include "server_sender.h"
#include "common_socket.h"

Sender::Sender(BlockingQueue<Command>& queue,
               ProtocolServer& protocol): queue(queue), protocol(protocol) {}

void Sender::run() {
    try {
        Command actComm;
        while (true) {
            actComm = this->queue.pop();
            try {
                this->protocol.sendCommand(actComm);
            } catch (ClosedSocketException const&) {} // Como un pez: nada
        }
    } catch (ClosedQueueException const&) {
        return;
}




Sender::~Sender() {
    this->join();
}
