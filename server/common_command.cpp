#include "common_command.h"

#include <exception>
#include <stdexcept>	
#include <arpa/inet.h>

Command::Command(): actTop(0), sender("HOST"), type(0xFF) {}


void Command::add8bitsMessage(const uint8_t message) {
    this->command.push_back(message);
}

void Command::add16bitsMessage(const uint16_t message) {
    uint16_t newMessage = htons(message);
    uint8_t* auxPoint = (uint8_t*)&newMessage;
    this->add8bitsMessage(auxPoint[0]);
    this->add8bitsMessage(auxPoint[1]);
}

void Command::add32bitsMessage(const uint32_t message) {
    uint32_t newMessage = htonl(message);
    uint8_t* auxPoint = (uint8_t*)&newMessage;
    this->add8bitsMessage(auxPoint[0]);
    this->add8bitsMessage(auxPoint[1]);
    this->add8bitsMessage(auxPoint[2]);
    this->add8bitsMessage(auxPoint[3]);
}

void Command::addString(const std::string& sent) {
    for (size_t i = 0; i < sent.size(); i++)
        this->add8bitsMessage((uint8_t)sent[i]);
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

uint8_t Command::pop8bitsMessage() {
    if (this->isEmpty())
        throw std::runtime_error("Tried to pop empty Command");
    uint8_t ret = this->command[this->actTop];
    this->actTop++;
    return ret;
}


uint16_t Command::pop16bitsMessage(){
    if (this->isEmpty())
        throw std::runtime_error("Tried to pop empty Command");
    uint8_t bytes[2];
    bytes[0] = this->pop8bitsMessage();
    bytes[1] = this->pop8bitsMessage();
    uint16_t* auxPoint = (uint16_t*)&bytes[0];
    return ntohs(*auxPoint);
}

uint32_t Command::pop32bitsMessage() {
    if (this->isEmpty())
        throw std::runtime_error("Tried to pop empty Command");
    uint8_t bytes[4];
    bytes[0] = this->pop8bitsMessage();
    bytes[1] = this->pop8bitsMessage();
    bytes[2] = this->pop8bitsMessage();
    bytes[3] = this->pop8bitsMessage();
    uint16_t* auxPoint = (uint16_t*)&bytes[0];
    return ntohl(*auxPoint);
}


std::string Command::popString(const size_t lenght) {
    std::string ret;
    ret.resize(lenght);
    for (size_t i = 0; i < lenght; i++) {
        ret[i] = (char)this->pop8bitsMessage();
    } 
    return ret;
}

Command::~Command() {}
