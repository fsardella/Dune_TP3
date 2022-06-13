#include "server_gameSet.h"
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>

/*
Pre-Condiciones: -
Post-Condiciones: Constructor del Conjunto De Games.
*/

GameSet::GameSet() {
}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega una Game al conjunto de Games y suma un participante
(el que creo la Game).
*/

int GameSet::add_game(int house, int required, const std::string& game_name,
                      const std::string& playerName, const std::string& mapPath) {
	const std::lock_guard<std::mutex> lock(m);
	if(game_exists(game_name)) {
		return ERROR;
	} else {
		Game game(required, game_name, mapPath);
		game.add_participant(house, playerName);
		games.push_back(std::move(game));
		return SUCCESS;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega a un vector de strings todos los nombres de las Games actuales.
*/


void GameSet::get_games_names(std::vector<std::string> *games_names) {
	for (size_t i = 0 ; i < games.size() ; i++) {
		games_names->push_back(games[i].get_name());
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega a una lista auxiliar las Games actuales con toda su informacion.
*/

void GameSet::list_games(std::vector<std::string> *games_names, std::list<GameData> *games_aux) {
	const std::lock_guard<std::mutex> lock(m);
	get_games_names(games_names);
	std::sort(games_names->begin(), games_names->end());
	for(size_t i = 0 ; i < games_names->size() ; i++) {
		Game& game = get_game(games_names->at(i));
		games_aux->push_back(GameData(game));
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Chequea si la Game existe (devuelve true) o si no existe (devuelve false).
*/

bool GameSet::game_exists(const std::string& game_name) {
	for (size_t i = 0 ; i < games.size() ; i++) {
		if((games[i].get_name()).compare(game_name) == 0) {
			return true;
		}
	}
	return false;
}

/*
Pre-Condiciones: -
Post-Condiciones: Chequea si la Game esta llena (devuelve true) o si no (devuelve false).
*/

bool GameSet::game_complete(const std::string& game_name) {
	Game& game = get_game(game_name);
	bool result = game.game_complete();
	return result;
}

/*
Pre-Condiciones: -
Post-Condiciones: Une a un participante a la Game. 
*/

int GameSet::game_join(int house, const std::string& game_name, const std::string& playerName) {
	const std::lock_guard<std::mutex> lock(m);
	if ((game_exists(game_name)) && !(game_complete(game_name))) {
		for (size_t i = 0 ; i < games.size() ; i++) {
			if ((games[i].get_name()).compare(game_name) == 0) {
				games[i].add_participant(house, playerName);
				break;
			}
		}
		if (game_complete(game_name)) {
			std::cout << "Comenzando Game " << game_name << "..." << std::endl;
		}
		return SUCCESS;
	}
	return ERROR;
}

/*
Pre-Condiciones: -
Post-Condiciones: Obtiene una Game especifica del vector de Games.
*/

Game& GameSet::get_game(const std::string& game_name) {
	for (size_t i = 0 ; i < games.size() ; i++) {
		if ((games[i].get_name()).compare(game_name) == 0) {
			return games[i];
		}
	}
	throw(std::invalid_argument("error al obtener la Game"));
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del Conjunto De Games.
*/

GameSet::~GameSet() {
}
