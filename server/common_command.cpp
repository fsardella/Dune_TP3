#include "common_command.h"

#include <arpa/inet.h>
#include <exception>
#include <stdexcept>

/*
 * Pre-condiciones: -
 * Post-condiciones: Constructor de la clase Command.
 * */

Command::Command(): actTop(0), sender("HOST"), type(0xFF) {}

/*
 * Pre-condiciones: -
 * Post-condiciones: Agrega el mensaje recibido por parámetro a la
 * lista de comandos.
 * */

void Command::add8bitsMessage(const uint8_t message) {
    this->command.push_back(message);
}

/*
 * Pre-condiciones: Agrega un mensaje de 16 bits a los comandos.
 * Post-condiciones: -
 * */

void Command::add16bitsMessage(const uint16_t message) {
    uint16_t newMessage = htons(message);
    uint8_t* auxPoint = (uint8_t*)&newMessage;
    this->add8bitsMessage(auxPoint[0]);
    this->add8bitsMessage(auxPoint[1]);
}

/*
 * Pre-condiciones: Agrega un mensaje de 32 bits a los comandos.
 * Post-condiciones: -
 * */

void Command::add32bitsMessage(const uint32_t message) {
    uint32_t newMessage = htonl(message);
    uint8_t* auxPoint = (uint8_t*)&newMessage;
    this->add8bitsMessage(auxPoint[0]);
    this->add8bitsMessage(auxPoint[1]);
    this->add8bitsMessage(auxPoint[2]);
    this->add8bitsMessage(auxPoint[3]);
}

/*
 * Pre-condiciones: Agrega un string a los comandos.
 * Post-condiciones: -
 * */

void Command::addString(const std::string& sent) {
    for (size_t i = 0; i < sent.size(); i++)
        this->add8bitsMessage((uint8_t)sent[i]);
}

/*
 * Pre-condiciones: Setea el tipo de comando a partir del recibido.
 * Post-condiciones: -
 * */

void Command::setType(const uint8_t newType) {
    this->type = newType;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el tipo de comando.
 * */

uint8_t Command::getType() {
    return this->type;
}

/*
 * Pre-condiciones: Reserva tanto espacio como newSize indica dentro
 * de los comandos.
 * Post-condiciones: -
 * */

void Command::reserve(const size_t newSize) {
    this->command.resize(newSize);
}

/*
 * Pre-condiciones: Cambia quien envia el comando a partir del nombre
 * del jugador recibido por parámetro.
 * Post-condiciones: -
 * */

void Command::changeSender(const std::string newName) {
    this->sender = newName;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el nombre del jugador que envía el comando.
 * */

std::string Command::getSender() {
    return this->sender;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el tamaño del comando.
 * */

size_t Command::size() {
    if (this->isEmpty())
        return 0;
    return this->command.size() - this->actTop;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un puntero al tope del comando.
 * */

uint8_t* Command::getPointer() {
    if (this->isEmpty())
        return nullptr;
    return &this->command[this->actTop];
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve true si el comando esta vacio, false
 * en caso contrario.
 * */

bool Command::isEmpty() {
    return this->command.size() <= this->actTop;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un número de 8 bits que popea del comando.
 * */

uint8_t Command::pop8bitsMessage() {
    if (this->isEmpty())
        throw std::runtime_error("Tried to pop empty Command");
    uint8_t ret = this->command[this->actTop];
    this->actTop++;
    return ret;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un número de 16 bits que popea del comando.
 * */

uint16_t Command::pop16bitsMessage(){
    if (this->isEmpty())
        throw std::runtime_error("Tried to pop empty Command");
    uint8_t bytes[2];
    bytes[0] = this->pop8bitsMessage();
    bytes[1] = this->pop8bitsMessage();
    uint16_t* auxPoint = (uint16_t*)&bytes[0];
    return ntohs(*auxPoint);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un número de 32 bits que popea del comando.
 * */

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

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un string que popea del comando.
 * */

std::string Command::popString(const size_t lenght) {
    std::string ret;
    ret.resize(lenght);
    for (size_t i = 0; i < lenght; i++) {
        ret[i] = (char)this->pop8bitsMessage();
    } 
    return ret;
}

/*
 * Pre-condiciones: Destructor de la clase Command.
 * Post-condiciones: -
 * */

Command::~Command() {}
