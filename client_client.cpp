#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <arpa/inet.h>
#include <vector>
#include <fstream>
#include <cstring>

#include "client_client.h"

#define HOUSE_ATREIDES "Atreides"
#define HOUSE_HARKONNEN "Harkonnen"
#define HOUSE_ORDOS "Ordos"
#define OPERACION_LISTAR "listar"
#define OPERACION_CREAR "crear"
#define OPERACION_UNIRSE "unirse"
#define OPERACION_FIN "fin"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Cliente.
*/

Client::Client(const char* name_host, const char* service_port):
protocol(name_host, service_port){
}

/*
Pre-Condiciones: -
Post-Condiciones: Determina el numero de la casa segun su nombre, y devuelve al numero.
*/

int Client::get_number_house(std::string& house) {
	if ((house.compare(HOUSE_HARKONNEN)) == 0) {
		return 0;
	} else if ((house.compare(HOUSE_ATREIDES)) == 0) {
		return 1; 
	} else if ((house.compare(HOUSE_ORDOS)) == 0) {
		return 2;
	} else {
		throw std::invalid_argument("Casa no valida");
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Imprime el resultado por la creacion de una Game.
*/

void Client::print_crear_result(int result) {
	if(result == 1) {
		std::cout << "Creacion fallida" << std::endl;
	} else {
		std::cout << "Creacion exitosa"  << std::endl;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Imprime el resultado por la creacion de una Game.
*/

void Client::print_unirse_result(int result) {
	if(result == 1) {
		std::cout << "Union fallida" << std::endl;
	} else {
		std::cout << "Union exitosa" << std::endl;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Lista el conjunto de Games existentes.
*/

void Client::print_listar_result() {
	int count = protocol.recieve_msg_count();
	uint8_t current_convert = 0;
	uint8_t required_convert = 0;
	std::string game_name_convert;
	for (int i = 0 ; i < count ; i++) {
		protocol.recieve_msg_listar(&current_convert,&required_convert,&game_name_convert);
		std::cout << game_name_convert << " " << protocol.convert_from_uint8(current_convert)
		<< "/" << protocol.convert_from_uint8(required_convert)  << std::endl;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Segun la operacion que requiera el jugador (listar, crear, unirse o fin) se
realizarán diferentes acciones. La operacion se lee desde entrada estandar.
*/

void Client::operation_run(std::string& line) {
	std::istringstream stream(line);
	stream >> operation;
	if (operation == OPERACION_LISTAR) {
		protocol.send_msg_listar();
		print_listar_result();
	} else if (operation == OPERACION_CREAR) {
		stream >> house >> num_players;
		int start = operation.length() + house.length() + num_players.length() + 3;
		game_name = line.substr(start, line.length());
		int house_number = get_number_house(house);
		protocol.send_msg_crear(house_number, std::stoi(num_players), game_name);
		int crear_result = protocol.recieve_msg_result();
		print_crear_result(crear_result);
	} else if (operation == OPERACION_UNIRSE) {
		stream >> house >> game_name;
		int house_number = get_number_house(house);
		protocol.send_msg_unirse(house_number,game_name);
		int result = protocol.recieve_msg_result();
		print_unirse_result(result);
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: El Cliente lee de entrada estandar y empieza a enviar y recibir respuestas 
por parte del Servidor.
*/

int Client::client_run() {
	std::string line;
    std::cout << "Ingrese nombre de jugador: ";
    std::getline(std::cin, line);
    protocol.sendMsgNombre(line);
	while (std::cin) {
		std::getline(std::cin, line);
		if (line == OPERACION_FIN)
			return 0;
		if (!line.empty()) {
			operation_run(line);
		}
	}
	return 0;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del cliente.
*/

Client::~Client() {
}
