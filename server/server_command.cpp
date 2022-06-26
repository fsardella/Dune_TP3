#include "server_command.h"

#include <exception>
#include <stdexcept>	
#include <arpa/inet.h>

Command::Command(): actTop(0), sender("HOST"), type(255) {}


void Command::add8BytesMessage(const uint8_t message) {
    this->command.push_back(message);
}

// Esta clase es la encargada del protocolo de comunicación?

void Command::add16BytesMessage(const uint16_t message) {
    uint16_t newMessage = htons(message);
    uint8_t* auxPoint = (uint8_t*)&newMessage;
    this->add8BytesMessage(auxPoint[0]);
    this->add8BytesMessage(auxPoint[1]);
}

void Command::setType(const uint8_t newType) {
    this->type = newType;
}

uint8_t Command::getType() {
    return this->type;
}

void Command::reserve(const size_t newSize) {
    this->command.resize(newSize);
}

void Command::changeSender(const std::string newName) {
    this->sender = newName;
}

std::string Command::getSender() {
    return this->sender;
}

size_t Command::size() {
    if (this->isEmpty())
        return 0;
    return this->command.size() - this->actTop;
}

uint8_t* Command::getPointer() {
    if (this->isEmpty())
        return nullptr;
    return &this->command[this->actTop];
}

bool Command::isEmpty() {
    return this->command.size() <= this->actTop;
}

uint8_t Command::pop8BytesMessage() {
    if (this->isEmpty())
        throw std::runtime_error("Tried to pop empty Command");
    uint8_t ret = this->command[this->actTop];
    this->actTop++;
    return ret;
}


uint16_t Command::pop16BytesMessage(){
    if (this->isEmpty())
        throw std::runtime_error("Tried to pop empty Command");
    uint8_t bytes[2];
    bytes[0] = this->pop8BytesMessage();
    bytes[1] = this->pop8BytesMessage(); // 8 bits == 1 Byte
    uint16_t* auxPoint = (uint16_t*)&bytes[0];
    return ntohs(*auxPoint);
}

Command::~Command() {}