#include "server_game.h"
#include <cstring>


Game::Game(): required(0) {}

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de una Game.
*/

Game::Game(unsigned int num_required, const std::string& name, const std::string& yamlMapPath):
required(num_required),game_name(name), yamlMapPath(yamlMapPath) {}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega un participante a la Game actual.
*/

void Game::add_participant(const int& ID_house, const std::string& playerName) {
	this->participants[playerName] = std::move(Player(ID_house, playerName));
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el juego esta completo o false si no.
*/

bool Game::game_complete() const{
	return (this->required <= this->participants.size());
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el nombre de la Game actual.
*/

std::string Game::get_name() const{
	return this->game_name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor de una Game.
*/

Game::~Game() {
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el numero de bytes del nombre de una Game.
*/

int Game::get_num_bytes() const{
	return this->game_name.length();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve los participantes actuales de una Game.
*/

int Game::get_participants() const{
	return this->participants.size();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve los participantes requeridos de una Game.
*/

int Game::get_required() const{
	return this->required;
}



bool Game::isPlaying(std::string playerName) {
    return (this->participants.find(playerName) != this->participants.end());
}


void Game::addUnit(std::string playerName, int x, int y, TerrainMap& terr) {
    if (!this->isPlaying(playerName))
        return;
    this->participants[playerName].addUnit(x, y, terr);
}


std::map<std::string, std::list<UnitData>> Game::getUnits() {
    std::map<std::string, std::list<UnitData>> result; 
    for (std::map<std::string, Player>::iterator it = this->participants.begin();
         it != this->participants.end();
         ++it) {
        result[it->first] = it->second.getUnits();
	}
    return result;
}

std::list<std::string> Game::getPlayerNames() {
    std::list<std::string> result;
    for (auto const& p : this->participants) {
        result.push_back(p.first);
    }
    return result;
}

int Game::getHouse(std::string playerName) {
    return (this->participants[playerName].getHouse());
}

Game::Game(Game&& other) : required(other.required),
                           game_name(std::move(other.game_name)),
                           participants(std::move(other.participants)),
                           yamlMapPath(std::move(other.yamlMapPath)) {}

Game& Game::operator=(Game&& other) {
    if (this == &other)
        return *this;
    this->game_name = std::move(other.game_name);
    this->participants = std::move(other.participants);
    this->yamlMapPath = std::move(other.yamlMapPath);
    this->required = other.required;
    other.required = 0;
    return *this;
}


