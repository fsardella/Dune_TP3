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

#include "server_command.h"
#include <exception>
#include <stdexcept>

typedef std::vector<std::vector<int>> sketch_t;

/*
Pre-Condiciones: -
Post-Condiciones: Constructor del hablador de Clientes.
*/

Talker::Talker(Socket&& socket, GameSet* game_set): protocol(std::move(socket)),
                                                    commandQueue(nullptr),
                                                    sender(nullptr) {
	try {
        this->gameSet = game_set;
        int bytes = this->protocol.recieve_msg_bytes();
        this->playerName = this->protocol.recieve_msg_game_name(bytes);
        std::cout << this->playerName << " connected..." << std::endl;  // DEBUG
    } catch (ClosedSocketException const&) {
        throw std::runtime_error("Socket disconnected before creation");
    }
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
	int result = gameSet->add_game(house,required,game_name, this->playerName, mapPath);
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

void Talker::list_maps() {
    std::vector<std::string> map_names;
    map_names.push_back("DEBUG_YAML_PATH");
    int size = (int)map_names.size();
	protocol.send_msg_num_list(size);
	for (const std::string& s : map_names)
        protocol.sendString(s);
}

/*
Pre-Condiciones: -
Post-Condiciones: Une a un jugador a una Game, en caso de que esta no este completa.
En caso de que se pueda unir al jugador, devuelve 0. Caso contrario devuelve 1.
*/

int Talker::join_game(int house, std::string& game_name) {
	int result = gameSet->game_join(house, game_name, this->playerName);
	return result;
}

std::string Talker::getPlayerName() {
    return this->playerName;
}

#define START_PLAYING 5

void Talker::startPlaying(BlockingQueue<Command>* newGameQueue, sketch_t gameMap,
                          BlockingQueue<Command>& sendingQueue) {
    this->protocol.send_msg_result(START_PLAYING);
    this->protocol.send_msg_num_list(gameMap.size());
    this->protocol.send_msg_num_list(gameMap[0].size());
    for (std::vector<int> row : gameMap) {
        this->protocol.send_map_row(row);
    }
    this->commandQueue = newGameQueue;
    this->sender = new Sender(sendingQueue, this->protocol);
    this->sender->start();
}


/*
Pre-Condiciones: -
Post-Condiciones: El hablador de clientes realiza diferentes acciones segun lo que determine
el Cliente (jugador). Estas pueden ser: unir al jugador a una Game, listar las 
Games existentes y/o crear una Game. 
*/

void Talker::run() {
	while (this->finishedThread() == false) {
		try {
            int operation = protocol.recieve_msg_operation();
            std::cout << "recibi la operacion: " << unsigned(operation) << std::endl;
            // GAME
            if (this->sender != nullptr) {
                Command comm;
                //int unitType = 0; // TODO que haga algo...
                switch (operation) {
                    case NEW_UNIT:
                        comm.reserve(5);
                        comm = protocol.recvCommand(5);
                        comm.setType(operation);
                        for (int i = 0; i < 5; i ++) {
                            std::cout << unsigned(comm.getPointer()[i]) << " ";
                        }
                        std::cout << "\n";
                        comm.changeSender(this->playerName);
                        std::cout << "ultima operacion: " << unsigned(comm.getType()) << std::endl;
                        this->commandQueue->push(comm);
                        break;
                }
                continue;
            }
            
            // LOBBY
            int house, bytes, result;
            std::string game_name;
            switch(operation) {
			    case UNIRSE:
				    bytes = protocol.recieve_msg_bytes();
				    game_name = protocol.recieve_msg_game_name(bytes);
                    house = protocol.recieve_msg_house();
                    result = join_game(house, game_name);
				    protocol.send_msg_result(result);
				    break;
			    case LISTAR:
				    list_games();
				    break;
			    case CREAR:
                    this->list_maps();
                    std::cout << "entre\n";
                    bytes = protocol.recieve_msg_bytes();
                    std::cout << "recibido " << bytes << std::endl;
				    std::string game_name = protocol.recieve_msg_game_name(bytes);
                    std::cout << "recibido " << game_name << std::endl;
				    bytes = protocol.recieve_msg_bytes();
				    std::string yamlPath = protocol.recieve_msg_game_name(bytes);
                    std::cout << "El mapa recibido es " << yamlPath << std::endl;
                    yamlPath = "DEBUG_YAML_PATH"; // DEBUG
                    house = protocol.recieve_msg_house();
				    //int required = readYaml(required);
                    int required = 1;
                    result = create_game(house,required,game_name, yamlPath);
				    protocol.send_msg_result(result);
			        break;
            }
        } catch (ClosedSocketException const&) {
            if (this->sender == nullptr) {
                this->finish = true;
                return;   
            }
            Command comm;
            comm.setType(DISCONNECT);
            comm.changeSender(this->playerName);
            this->commandQueue->push(comm);
            this->finish = true;
        }
    }
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del hablador de Clientes.
*/

Talker::~Talker() {
    if (this->sender != nullptr)
	    delete this->sender;
    this->join();
    std::cout << this->playerName << " disconnected..." << std::endl; // DEBUG
}