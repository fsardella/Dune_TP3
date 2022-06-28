#include "server_game.h"
#include <cstring>


Game::Game(): required(0) {}

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de una Game.
*/

Game::Game(unsigned int num_required, const std::string& name, const std::string& yamlMapPath):
required(num_required),game_name(name), yamlMapPath(yamlMapPath) {
    //this->basesCoordinates <= yamlMapPath.COORDENADAS_DE_BASES
    this->basesCoordinates.push_back(coor_t(16, 16));
    this->basesCoordinates.push_back(coor_t((41 - 8) * 8, (41 - 8) * 8));
}

/*
Pre-Condiciones: -
Post-Condiciones: Agrega un participante a la Game actual.
*/

void Game::add_participant(const int& ID_house, const std::string& playerName) {
	this->participants[playerName] = std::move(Player(ID_house, playerName,
                                     basesCoordinates.front()));
    basesCoordinates.pop_front();
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


uint8_t Game::getUnitFactor(std::string playerName, uint8_t type) {
    return this->participants[playerName].getUnitFactor(type);
}

coor_t Game::getUnitDir(std::string playerName, uint8_t type, TerrainMap& terr) {
    return this->participants[playerName].getUnitDir(type, terr);
}


bool Game::addUnit(std::string playerName, Unit* unit, uint8_t id) {
    if (!this->isPlaying(playerName))
        return false;
    this->participants[playerName].addUnit(unit, id);
    return true;
}

bool Game::addBuilding(std::string playerName, uint8_t type,
                   uint16_t x, uint16_t y, TerrainMap& terr, uint16_t id) {
    if (!this->isPlaying(playerName))
        return false;
    return this->participants[playerName].addBuilding(type, x, y, terr, id);
}

void Game::moveUnit(std::string playerName, uint16_t unitID, coor_t coor) {
    if (!this->isPlaying(playerName))
        return;
    this->participants[playerName].moveUnit(unitID, coor);
}

void Game::updateUnits() {
    for (auto& p : this->participants)
        p.second.updateUnits();
}

uint8_t Game::getPlayerID(std::string playerName) {
    return this->participants[playerName].getID();
}

std::map<uint8_t, std::list<UnitData>> Game::getUnits() {
    std::map<uint8_t, std::list<UnitData>> result; 
    for (std::map<std::string, Player>::iterator it = this->participants.begin();
         it != this->participants.end();
         ++it) {
        result[it->second.getID()] = it->second.getUnits();
	}
    return result;
}

std::list<PlayerData> Game::buildBases(TerrainMap& terr) {
    std::list<PlayerData> result;
    uint16_t id = 0;
    for (auto& p : this->participants) {
        p.second.buildBase(terr, id);
        result.push_back(PlayerData(p.first, p.second.getHouse(),
                                    p.second.getBaseCoords()));
        id++;
    }
    return result;
}

void Game::setPlayerID(std::string playerName, uint8_t id) {
    this->participants[playerName].setID(id);
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


