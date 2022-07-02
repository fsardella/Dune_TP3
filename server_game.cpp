#include "server_game.h"
#include <cstring>


#ifndef BROADCASTOPERS
#define BROADCASTOPERS
enum broadcastOpers {
    SUCCESS = 0,
    FAILURE,
    UNIT_BROADCAST,
    BUILDING_BUILT,
    UNIT_ATTACKED,
    BUILDING_ATTACKED,
    LOST_GAME,
    WON_GAME,
    UNIT_WIP,
    BUILDING_WIP,
    WORM,
    MENAGE
};
#endif




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

Unit* Game::getUnit(std::string playerName, uint16_t unitID) {
    if (!this->isPlaying(playerName) 
        || !this->participants[playerName].hasLost())
        return nullptr;
    return this->participants[playerName].getUnit(unitID);
}


Building* Game::getBuilding(std::string playerName, uint16_t buildingID) {
    if (!this->isPlaying(playerName) 
        || !this->participants[playerName].hasLost())
        return nullptr;
    return this->participants[playerName].getBuilding(buildingID);
}


bool Game::addUnit(std::string playerName, Unit* unit) {
    if (!this->isPlaying(playerName) 
        || !this->participants[playerName].hasLost())
        return false;
    this->participants[playerName].addUnit(unit);
    return true;
}

void Game::createBuilding(std::string playerName, uint8_t type) {
    if (!this->isPlaying(playerName) 
        || !this->participants[playerName].hasLost())
        return;
    this->participants[playerName].createBuilding(type);
}

uint16_t Game::addBuilding(std::string playerName, uint16_t x, uint16_t y,
                       TerrainMap& terr, uint16_t id) {
    if (!this->isPlaying(playerName) 
        || !this->participants[playerName].hasLost())
        return 0xFFFF;
    return this->participants[playerName].addBuilding(x, y, terr, id);
}

void Game::moveUnit(std::string playerName, uint16_t unitID, coor_t coor) {
    if (!this->isPlaying(playerName) 
        || !this->participants[playerName].hasLost())
        return;
    this->participants[playerName].moveUnit(unitID, coor);
}

void Game::updateUnits(std::list<Command>& events) {
    for (auto& p : this->participants)
        p.second.updateUnits(events);
}

void Game::updateBuildings() {
    for (auto& p : this->participants)
        p.second.updateBuildings();
}

bool Game::chargeMoney(std::string playerName, uint8_t type) {
    if (!this->isPlaying(playerName) 
        || !this->participants[playerName].hasLost())
        return false;
    return this->participants[playerName].chargeMoney(type);
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

std::map<uint8_t, std::pair<uint32_t, int32_t>> Game::getPlayersResources() {
    std::map<uint8_t, std::pair<uint32_t, int32_t>> ret;
    for (auto& p : this->participants) {
        ret[p.second.getID()] = std::pair<uint32_t, int32_t>(p.second.getMoney(),
                                                    p.second.getEnergy());
    }
    return ret;
}

void Game::getBuildingsBuilding(std::map<uint8_t,
                                std::pair<uint8_t, uint8_t>>& buildingInfo) {
    for (auto& p : this->participants) {
        std::pair<uint8_t, uint8_t> data = p.second.getBuildingInfo();
        if (data.first != 0xFF)
            buildingInfo[p.second.getID()] = data;
    }
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



void Game::cleanCorpses(std::map<uint16_t, std::string>& unitIDs,
                      std::map<uint16_t, std::string>& buildingIDs,
                      std::list<Command>& events) {
    auto p = this->participants.begin();
    if (this->participants.size() == 1 && !this->decidedWinner) {
        Command win;
        win.changeSender(p->first);
        win.setType(WON_GAME);
        win.add8BytesMessage(WON_GAME);
        this->decidedWinner = true;
        events.push_back(win);
        return;
    }
    while (p != this->participants.end()) {
        if (p->second.canBeCleaned()) {
            Command lost;
            lost.changeSender(p->first);
            lost.setType(LOST_GAME);
            lost.add8BytesMessage(LOST_GAME);
            events.push_back(lost);
            p = this->participants.erase(p);
        } else {
            p->second.cleanCorpses(unitIDs, buildingIDs, events);
            p++;
        }
    }
}

void Game::disconnect(std::string disconnected, std::list<Command>& events) {
    if (!this->isPlaying(disconnected) 
        || !this->participants[disconnected].hasLost())
        return;
    this->participants[disconnected].kill(events);
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


