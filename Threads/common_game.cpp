#include "common_game.h"
#include <cstring>

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de una partida.
*/

Game::Game(int ID_house, int num_required, std::string& name): house(ID_house),
required(num_required),game_name(name),participants(0) {
}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega un participante a la partida actual.
*/

void Game::add_participant() {
	this->participants++;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve true si el juego esta completo o false si no.
*/

bool Game::game_complete() {
	if (required == participants) return true;
	return false;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el nombre de la partida actual.
*/

std::string Game::get_name() {
	return this->game_name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor de una partida.
*/

Game::~Game() {
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve el numero de bytes del nombre de una partida.
*/

int Game::get_num_bytes(){
	return this->game_name.length();
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve los participantes actuales de una partida.
*/

int Game::get_participants(){
	return this->participants;
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve los participantes requeridos de una partida.
*/

int Game::get_requiered(){
	return this->required;
}

