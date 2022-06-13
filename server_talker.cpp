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
#include "server_gamedata.h"
#include "server_gameSet.h"

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
Post-Condiciones: Crea una Game.
*/

int Talker::create_game(int house, int required, const std::string& game_name,
                        const std::string& mapPath) {
    std::string playerName = "DEBUG_P_NAME";
	int result = gameSet->add_game(house,required,game_name, playerName, mapPath);
	return result;
}

/*
Pre-Condiciones: -
Post-Condiciones: Lista en orden alfabetico las Games existentes. 
*/

void Talker::list_games() {
	try {
		std::vector<std::string> games_names;
		std::list<GameData> games_aux;
		gameSet->list_games(&games_names, &games_aux);
		int size = (int)games_aux.size();
		protocol.send_msg_num_list(size);
		for(int i = 0 ; i < size ; i++) {
			protocol.send_msg_list(games_aux.front());
			games_aux.pop_front();
		}
	}
	catch(std::invalid_argument const&){
		std::cerr << "Error al obtener la Game." << std::endl;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Une a un jugador a una Game, en caso de que esta no este completa.
En caso de que se pueda unir al jugador, devuelve 0. Caso contrario devuelve 1.
*/

int Talker::join_game(int house, std::string& game_name) {
    std::string playerName = "DEBUG_P_NAME";
	int result = gameSet->game_join(house, game_name, playerName);
	return result;
}

/*
Pre-Condiciones: -
Post-Condiciones: El hablador de clientes realiza diferentes acciones segun lo que determine
el Cliente (jugador). Estas pueden ser: unir al jugador a una Game, listar las 
Games existentes y/o crear una Game. 
*/

void Talker::run() {
	while (finishedThread() == false) {
		try {
            int operation = protocol.recieve_msg_operation();
		    int house, bytes, result;
            std::string game_name;
            switch(operation) {
			    case UNIRSE:
				    house = protocol.recieve_msg_house();
				    bytes = protocol.recieve_msg_bytes();
				    game_name = protocol.recieve_msg_game_name(bytes);
				    result = join_game(house, game_name);
				    protocol.send_msg_result(result);
				    break;
			    case LISTAR:
				    list_games();
				    break;
			    case CREAR:
				    house = protocol.recieve_msg_house();
				    int required = protocol.recieve_msg_required();
				    bytes = protocol.recieve_msg_bytes();
				    std::string game_name = protocol.recieve_msg_game_name(bytes);
                    std::string yamlPath = "DEBUG_YAML_PATH";
				    result = create_game(house,required,game_name, yamlPath);
				    protocol.send_msg_result(result);
			        break;
            }
        } catch (ClosedSocketException const&) {
            this->finish = true;
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
