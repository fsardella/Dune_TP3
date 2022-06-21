#include "server_gameSet.h"
//#include <cstring>
//#include <iostream>
//#include <functional>
//#include <algorithm>

typedef std::lock_guard<std::mutex> lock_t;

/*
Pre-Condiciones: -
Post-Condiciones: Constructor del Conjunto De Games.
*/

GameSet::GameSet(BlockingQueue<Game>& readyGames): readyGames(readyGames) {}


/*
Pre-Condiciones: -
Post-Condiciones: Chequea si la Game existe (devuelve true) o si no existe (devuelve false).
*/

bool GameSet::game_exists(const std::string& game_name) {
	return (this->games.find(game_name) != this->games.end());
}

/*
Pre-Condiciones: Existe un juego game_name.
Post-Condiciones: Chequea si la Game esta llena (devuelve true) o si no (devuelve false).
*/

bool GameSet::game_complete(const std::string& game_name) {
	//Game& game = get_game(game_name);
    return (this->games[game_name].game_complete());
}



/*
Pre-Condiciones: -
Post-Condiciones: Agrega una Game al conjunto de Games y suma un participante
(el que creo la Game).
*/

int GameSet::add_game(int house, int required, const std::string& game_name,
                      const std::string& playerName, const std::string& mapPath) {
	lock_t lock(this->m);
	if (this->game_exists(game_name)) {
		return ERROR;
	} else {
		Game newGame(required, game_name, mapPath);
		newGame.add_participant(house, playerName);
		this->games[game_name] = std::move(newGame);
		if (this->game_complete(game_name)) {
            readyGames.push(std::move(this->games[game_name]));
            this->games.erase(game_name);
			//std::cout << "Comenzando Game " << game_name << "..." << std::endl;
		}
		return SUCCESS;
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega a un vector de strings todos los nombres de las Games actuales.
*/


//void GameSet::get_games_names(std::vector<std::string> *games_names) {
	//for (auto const& gameTuple : this->games) {
        
    //}
//}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega a una lista auxiliar las Games actuales con toda su informacion.
*/

void GameSet::list_games(std::vector<std::string> *games_names, std::list<GameData> *games_aux) {
    lock_t lock(this->m);
	//get_games_names(games_names);
    for (std::map<std::string, Game>::iterator it = this->games.begin();
         it != this->games.end();
         ++it) {
        games_names->push_back(it->first);
		games_aux->push_back(GameData(it->second));
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Une a un participante a la Game. 
*/

int GameSet::game_join(int house, const std::string& game_name, const std::string& playerName) {
	lock_t lock(this->m);
	if (this->game_exists(game_name) && !this->game_complete(game_name)) {
        this->games[game_name].add_participant(house, playerName);
		if (this->game_complete(game_name)) {
            readyGames.push(std::move(this->games[game_name]));
            this->games.erase(game_name);
			//std::cout << "Comenzando Game " << game_name << "..." << std::endl;
		}
		return SUCCESS;
	}
	return ERROR;
}

/*
Pre-Condiciones: -
Post-Condiciones: Obtiene una Game especifica del vector de Games.
*/

//Game& GameSet::get_game(const std::string& game_name) {
	//for (size_t i = 0 ; i < games.size() ; i++) {
		//if ((games[i].get_name()).compare(game_name) == 0) {
			//return games[i];
		//}
	//}
	//throw(std::invalid_argument("error al obtener la Game"));
//}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del Conjunto De Games.
*/

GameSet::~GameSet() {
}

GameSet::GameSet(GameSet&& other) :
                           games(std::move(other.games)),
                           readyGames(other.readyGames) {}

GameSet& GameSet::operator=(GameSet&& other) {
    if (this == &other)
        return *this;
    this->games = std::move(other.games);
    this->readyGames = std::move(other.readyGames);
    return *this;
}

