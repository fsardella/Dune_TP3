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
#include <list>
#include "server_talker.h"
#include "common_game.h"
#include "common_gameSet.h"

/*
Pre-Condiciones: -
Post-Condiciones: Constructor del hablador de Clientes.
*/

Talker::Talker(Socket&& socket, GameSet* game_set): protocol(std::move(socket)) {
	this->gameSet = game_set;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el hilo del cliente actual finalizó o false si no lo hizo.
*/

bool Talker::finishedThread() {
	return this->finish;
}

/*
Pre-Condiciones: -
Post-Condiciones: Crea una partida.
*/

int Talker::create_game(int house, int required, std::string& game_name) {
	int result = gameSet->add_game(house,required,game_name);
	return result;
}

/*
Pre-Condiciones: -
Post-Condiciones: Lista en orden alfabetico las partidas existentes. 
*/

void Talker::list_games() {
	try {
		std::vector<std::string> games_names;
		std::list<Game> games_aux;
		gameSet->list_games(&games_names, &games_aux);
		int size = (int)games_aux.size();
		protocol.send_msg_num_list(size);
		for(int i = 0 ; i < size ; i++) {
			protocol.send_msg_list(games_aux.front());
			games_aux.pop_front();
		}
	}
	catch(std::invalid_argument const&){
		std::cerr << "Error al obtener la partida." << std::endl;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Une a un jugador a una partida, en caso de que esta no este completa.
En caso de que se pueda unir al jugador, devuelve 0. Caso contrario devuelve 1.
*/

int Talker::join_game(int house, std::string& game_name) {
	int result = gameSet->game_join(game_name);
	return result;
}

/*
Pre-Condiciones: -
Post-Condiciones: El hablador de clientes realiza diferentes acciones segun lo que determine
el Cliente (jugador). Estas pueden ser: unir al jugador a una partida, listar las 
partidas existentes y/o crear una partida. 
*/

void Talker::run() {
	while (finishedThread() == false) {
		int operation = protocol.recieve_msg_operation();
		switch(operation) {
			case FIN: {
				this->finish = true;
				break;
			}
			case UNIRSE: {
				int house = protocol.recieve_msg_house();
				int bytes = protocol.recieve_msg_bytes();
				std::string game_name = protocol.recieve_msg_game_name(bytes);
				int result = join_game(house, game_name);
				protocol.send_msg_result(result);
				break;
			}
			case LISTAR: {
				list_games();
				break;
			}
			case CREAR: {
				int house = protocol.recieve_msg_house();
				int requeried = protocol.recieve_msg_required();
				int bytes = protocol.recieve_msg_bytes();
				std::string game_name = protocol.recieve_msg_game_name(bytes);
				int result = create_game(house,requeried,game_name);
				protocol.send_msg_result(result);
			}
			break;
		}
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del hablador de Clientes.
*/

Talker::~Talker() {
	this->join();
}
