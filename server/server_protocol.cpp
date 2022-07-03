#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdint>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <string>

#include "server_talker.h"
#include "server_game.h"
#include "server_gameSet.h"
#include "server_protocol.h"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Protocolo.
*/

ProtocolServer::ProtocolServer(Socket&& accept): socket(std::move(accept)) {
}

/*
Pre-Condiciones: -
Post-Condiciones: (Serializacion) Pasa de un int a un uint16_t, pasandolo a BE. 
*/

uint16_t ProtocolServer::convert_to_uint16_with_endianess(int number){
	int num_aux = htons((uint16_t) number);
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: (Serializacion) Pasa de un int a un uint8_t. 
*/

uint8_t ProtocolServer::convert_to_uint8(int number){
	uint8_t num_aux = (uint8_t) number;
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Pasa de un uint8_t a un int. 
*/

int ProtocolServer::convert_from_uint8(uint8_t number){
	int num_aux = (int) number;
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Pasa de un uint16_t a un int, pasandolo a LE. 
*/

int ProtocolServer::convert_from_uint16_with_endianess(uint16_t number){
	int num_aux = ntohs((int) number);
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del protocolo.
*/

ProtocolServer::~ProtocolServer() {
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe el mensaje de la operacion que quiere realizar el cliente actual.
En caso de haber escrito "fin" por entrada estandar, no va a recibir nada y el skt se va a
setear a cerrado = true.
*/

int ProtocolServer::recieve_msg_operation() {
	uint8_t operation_convert = 0;
    socket.recvall(&operation_convert,1); 
	int operation = convert_from_uint8(operation_convert);
	return operation;
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe mensaje sobre la casa por parte del Cliente. 
*/

int ProtocolServer::recieve_msg_house() {
	uint8_t house_convert = 0;
	socket.recvall(&house_convert,1);
	int house = convert_from_uint8(house_convert);
	return house;
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe mensaje sobre la cantidad de jugadores 
requerida por parte del Cliente.
*/

int ProtocolServer::recieve_msg_required() {
	uint8_t required_convert = 0;
	socket.recvall(&required_convert,1);
	int required = convert_from_uint8(required_convert);
	return required;
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe mensaje sobre la cantidad de bytes
que tiene el nombre de un x juego, por parte del Cliente.
*/

int ProtocolServer::recieve_msg_bytes() {
	uint16_t bytes_convert = 0;
	socket.recvall(&bytes_convert,2);
	int bytes = convert_from_uint16_with_endianess(bytes_convert);
	return bytes;
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe mensaje sobre el nombre del juego, 
por parte del Cliente.
*/

std::string ProtocolServer::recieve_msg_game_name(int bytes) {
	std::string game_name;
    game_name.resize(bytes);
    socket.recvall(&game_name[0], bytes);
	return game_name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Envia mensaje como respuesta a si se pudo realizar
una accion exitosa en el juego o no. Envia el mensaje al Cliente.
*/

void ProtocolServer::send_msg_result(int response) {
	int response_convert = convert_to_uint8(response);
	socket.sendall(&response_convert, 1);
}

/*
Pre-Condiciones: -
Post-Condiciones: Envia mensaje como respuesta a la cantidad de
Games que se van a listar.
*/

void ProtocolServer::send_msg_num_list(int size) {
	uint16_t count_convert = convert_to_uint16_with_endianess(size);
	socket.sendall(&count_convert, 2);
}

/*
Pre-Condiciones: -
Post-Condiciones: Envia los mensajes para que el cliente pueda 
tener la informacion para listar las Games actuales.
*/

void ProtocolServer::send_msg_list(GameData game) {
	uint8_t num_participants_convert = convert_to_uint8(game.get_participants());
	socket.sendall(&num_participants_convert, 1);

	uint8_t num_required_convert = convert_to_uint8(game.get_required());
	socket.sendall(&num_required_convert, 1);

	int num_bytes = game.get_num_bytes();
	uint16_t num_bytes_convert = convert_to_uint16_with_endianess(num_bytes);
	socket.sendall(&num_bytes_convert, 2);

	for(int i = 0 ; i < num_bytes ; i++) {
		socket.sendall(&game.get_name().at(i), 1);
	}
}

void ProtocolServer::send_map_row(std::vector<int>& row) {
    int size = row.size();
    std::vector<uint8_t> newRow;
    for (int elem: row)
        newRow.push_back((u_int8_t) elem);
    this->socket.sendall(&newRow[0], size);
}

void ProtocolServer::sendCommand(Command command) {
    int size = command.size();
    uint16_t newSize = convert_to_uint16_with_endianess(size);
    this->socket.sendall(&newSize, 2);
    this->socket.sendall(command.getPointer(), size);    
}

Command ProtocolServer::recvCommand(int size) {
    Command newCommand;
    newCommand.reserve(size + 1);
    this->socket.recvall(newCommand.getPointer(), size);   
    return newCommand; 
}

void ProtocolServer::sendString(const std::string& data) {
	int size = data.size();
	uint16_t newSize = convert_to_uint16_with_endianess(size);
    this->socket.sendall(&newSize, 2);
    this->socket.sendall(&data[0], size);
}
