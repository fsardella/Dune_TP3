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

#include "common_command.h"
#include <exception>
#include <stdexcept>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>



typedef std::vector<std::vector<int>> sketch_t;

/*
Pre-Condiciones: -
Post-Condiciones: Constructor del hablador de Clientes.
*/

Talker::Talker(Socket&& socket, GameSet* game_set,
               Config* c): c(c), protocol(std::move(socket)),
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
	int result = gameSet->add_game(house,required,game_name, this->playerName,
                                   mapPath, c);
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
    try {
        YAML::Node node = YAML::LoadFile(c->MAP_NAMES_PATH);
        std::vector<std::string> map_names = node["maps"].as<
                                        std::vector<std::string>>();
        int size = (int)map_names.size();
        protocol.send_msg_num_list(size);
	    for (const std::string& s : map_names)
            protocol.sendString(s);
    } catch(YAML::BadFile& e) {
        throw(std::runtime_error("No map has been created"));
    }
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
                          std::list<PlayerData> names,
                          BlockingQueue<Command>& sendingQueue) {
    try {
        this->protocol.send_msg_result(START_PLAYING);
        this->protocol.send_msg_num_list(gameMap.size());
        this->protocol.send_msg_num_list(gameMap[0].size());
        for (std::vector<int> row : gameMap) {
            this->protocol.send_map_row(row);
        }
        this->protocol.send_msg_result(names.size());
        for (PlayerData& data : names) {
            this->protocol.sendString(data.name);
            this->protocol.send_msg_num_list(data.base.second);
            this->protocol.send_msg_num_list(data.base.first);
            this->protocol.send_msg_result(data.house);
        }
    } catch (ClosedSocketException const&) {
        sendingQueue.close();
        return;
    }
    this->commandQueue = newGameQueue;
    this->sender = new Sender(sendingQueue, this->protocol);
    this->sender->start();
}

void Talker::handleLobby(int operation) {
    int house, result, bytes;
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
            bytes = protocol.recieve_msg_bytes();
            game_name = protocol.recieve_msg_game_name(bytes);
            bytes = protocol.recieve_msg_bytes();
            std::string yamlPath = protocol.recieve_msg_game_name(bytes);
            house = protocol.recieve_msg_house();
            YAML::Node node = YAML::LoadFile(c->MAP_PATHS + yamlPath + ".yaml");
            int required = node["constructions"].as<std::vector<
                           std::vector<int>>>().size();
            result = create_game(house,required,game_name, yamlPath);
            protocol.send_msg_result(result);
            break;
    }
}



void Talker::handleGame(int operation) {
    Command comm;
    int bytes;
    switch (operation) {
        case UNIRSE: // Estan para evitar race conditions
            bytes = protocol.recieve_msg_bytes();
            protocol.recieve_msg_game_name(bytes);
            protocol.recieve_msg_house();
            return; // IGNORE COMMAND!
        case CREAR: // Estan para evitar race conditions
            bytes = protocol.recieve_msg_bytes();
            protocol.recieve_msg_game_name(bytes);
            bytes = protocol.recieve_msg_bytes();
            protocol.recieve_msg_game_name(bytes);
            protocol.recieve_msg_house();
            return; // IGNORE COMMAND!
        case NEW_UNIT:
            bytes = 1;
            break;
        case NEW_BUILDING:
            bytes = 1;
            break;
        case ATTACK:
            bytes = 5;
            break;
        case MOVE:
            bytes = 6;
            break;
        case ADD_BUILDING:
            bytes = 4;
            break;
        case DESTROY_BUILDING:
            bytes = 2;
            break;
        default:
            return;
    }
    comm.reserve(bytes); // CHANGE
    comm = protocol.recvCommand(bytes);
    comm.setType(operation);
    comm.changeSender(this->playerName);
    this->commandQueue->push(comm);
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
            if (this->sender != nullptr) // GAME
                this->handleGame(operation);
            else  // LOBBY
                this->handleLobby(operation);
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
