#include "server_game.h"
#include <cstring>

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
	this->participants.push_back(std::move(Player(ID_house, playerName)));
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el juego esta completo o false si no.
*/

bool Game::game_complete() {
	return (this->required <= this->participants.size());
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el nombre de la Game actual.
*/

std::string Game::get_name() {
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

int Game::get_num_bytes(){
	return this->game_name.length();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve los participantes actuales de una Game.
*/

int Game::get_participants(){
	return this->participants.size();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve los participantes requeridos de una Game.
*/

int Game::get_required(){
	return this->required;
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


