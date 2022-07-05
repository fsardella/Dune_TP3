#include "server_activegame.h"
#include "server_units.h"
#include "server_buildings.h"

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>

#include <vector>
#include <utility>
#include <iostream>


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

/*
 * Pre-condiciones: -
 * Post-condiciones: Constructor de la clase ActiveGame.
 * */

ActiveGame::ActiveGame(Game game, Config* c): c(c),
                                   buildingIDCount(game.get_required()),
                                   game(std::move(game)),
                                   adorableLittleWorm(Worm(
                                   this->gameMap, c->WORM_DELAY)) {
    YAML::Node node = YAML::LoadFile(c->MAP_PATHS + this->game.getMapPath() +
                                     ".yaml");
    this->gameMapSketch = node["matrix"].as<std::vector<std::vector<int>>>();
    this->gameMap = TerrainMap(this->gameMapSketch);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve verdadero si la unidad recibida se
 * encuentra en las existentes, false en caso contrario.
 * */

bool ActiveGame::hasUnit(uint16_t unitID) {
    return (this->unitIDs.find(unitID) != this->unitIDs.end());
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve verdadero si el edificio recibido se
 * encuentra en las existentes, false en caso contrario.
 * */

bool ActiveGame::hasBuilding(uint16_t buildingID) {
    return (this->buildingIDs.find(buildingID) != this->buildingIDs.end());
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve una lista con la información de los
 * jugadores.
 * */

std::list<PlayerData> ActiveGame::getPlayersData() {
    lock_t lock(this->m);
    std::list<PlayerData> ret = this->game.buildBases(this->gameMap);
    uint16_t id = 0;
    for (PlayerData& p : ret) {
        this->game.setPlayerID(p.name, id);
        this->buildingIDs[id] = p.name;
        id++;
    }
    return ret;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un elemento de tipo sketch_t del mapa.
 * */

sketch_t ActiveGame::getMapSketch() {
    return this->gameMapSketch;
    // No tiene mutex porque gameMapSketch solo cambia en
    // el constructor.
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Termina la partida.
 * */

void ActiveGame::endGame() {
    lock_t lock(this->m);
    this->alive = false;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve verdadero si la partida esta activa,
 * false en caso contrario.
 * */

bool ActiveGame::isAlive() {
    lock_t lock(this->m);
    return this->alive;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Actualiza el buffer de las unidades.
 * */

void ActiveGame::updateUnitsBuffer() {
    std::list<UnitBuffer>::iterator it = unitsBuilding.begin();
    coor_t validDir;
    uint16_t factor;
    while (it != unitsBuilding.end()) {
        if (!this->game.isPlaying(it->getPlayerName())) {
            it = unitsBuilding.erase(it);
            continue;
        }
        factor = this->game.getUnitFactor(it->getPlayerName(), it->getType());
        if (factor == 0) {
            it = unitsBuilding.erase(it);
            continue;
        }
        if (it->willItEnd(factor)) {
            validDir = this->game.getUnitDir(it->getPlayerName(),
                                             it->getType(),
                                             this->gameMap);
            if (validDir == coor_t(0, 0)) {
                std::cout << "invalid dir\n";
                it++;
                continue;
            }
            this->game.addUnit(it->getPlayerName(),
                               it->getResult(validDir, this->unitIDCount));
            this->unitIDs[this->unitIDCount] = it->getPlayerName();
            this->unitIDCount++;
            it = unitsBuilding.erase(it);
        } else {
            it->process(factor);
            it++;
        }
    }
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un mapa con la información de las unidades.
 * */

std::map<uint8_t, std::list<UnitData>> ActiveGame::getUnits() {
    return this->game.getUnits();
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve una lista de comandos generados
 * por eventos.
 * */

std::list<Command> ActiveGame::receiveEvents() {
    std::list<Command> ret(this->events);  // Copy list
    this->events.clear();
    return ret;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve una lista con el buffer de las
 * unidades.
 * */

std::list<UnitBuffer> ActiveGame::receiveUnitBuffer() {
    std::list<UnitBuffer> ret(this->unitsBuilding);  // Copy list
    return ret;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve una lista de comandos generados
 * por edificios.
 * */

std::list<Command> ActiveGame::receiveBuildingsBuilding() {
    std::list<Command> ret;
    std::map<uint8_t, std::pair<uint8_t, uint8_t>> result;
    this->game.getBuildingsBuilding(result);
    for (auto& c : result) {
        Command comm;
        comm.add8bitsMessage(BUILDING_WIP);
        comm.setType(BUILDING_WIP);
        comm.changeSender(this->buildingIDs[c.first]);
        comm.add8bitsMessage(c.second.first);
        comm.add8bitsMessage(c.second.second);
        ret.push_back(comm);
    }
    return ret;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un mapa con los recursos del jugador.
 * */

std::map<uint8_t, std::pair<uint32_t, int32_t>>
        ActiveGame::getPlayersResources() {
    return this->game.getPlayersResources();
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve una lista con la información de la
 * especia.
 * */

std::list<std::pair<coor_t, uint16_t>> ActiveGame::getMenageData() {
    std::list<std::pair<coor_t, uint16_t>> ret;
    this->gameMap.addMenageData(ret);
    return ret;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el broadscast de la partida.
 * */

broadcast_t ActiveGame::getBroadcast() {
    lock_t lock(this->m);
    return broadcast_t(this->getUnits(),
                       this->getPlayersResources(),
                       this->receiveEvents(),
                       this->receiveUnitBuffer(),
                       this->receiveBuildingsBuilding(),
                       this->getMenageData());
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Swappea una unidad entre jugadores.
 * */

void ActiveGame::swapUnits() {
    for (auto& swapped : this->swappedUnits) {
        if (!this->hasUnit(swapped.first))
            continue;
        this->game.swapUnits(this->unitIDs[swapped.first],
                             swapped.second,
                             swapped.first);
        this->unitIDs[swapped.first] = swapped.second;
    }
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Actualiza el estado de la partida.
 * */

void ActiveGame::update() {
    lock_t lock(this->m);
    this->updateUnitsBuffer();
    this->game.updateUnits(this->events);
    this->game.updateBuildings();
    this->adorableLittleWorm.update(this->events);
    this->swapUnits();
    this->game.cleanCorpses(this->unitIDs, this->buildingIDs, this->events);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Agrega una unidad.
 * */

void ActiveGame::addUnit(std::string playerName, uint8_t type) {
    lock_t lock(this->m);
    for (UnitBuffer& un : this->unitsBuilding) {
        if (playerName == un.getPlayerName() && type == un.getType())
            return;
    }
    bool ret = this->game.chargeMoney(playerName, type);
    if (ret)
        this->unitsBuilding.push_back(UnitBuffer(type, playerName,
                                                this->gameMap,
                                            this->game.getPlayerID(playerName),
                                            c,
                                            this->events, this->swappedUnits));
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Construye un edificio.
 * */

void ActiveGame::createBuilding(std::string playerName, uint8_t type) {
    lock_t lock(this->m);
    this->game.createBuilding(playerName, type);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Agrega un edificio.
 * */

bool ActiveGame::addBuilding(std::string playerName, uint16_t x, uint16_t y) {
    lock_t lock(this->m);
    uint16_t ret = this->game.addBuilding(playerName, x, y,
                                      this->gameMap, this->buildingIDCount);
    if (ret != 0xFFFF) {
        Command newEvent;
        newEvent.add8bitsMessage(BUILDING_BUILT);
        newEvent.setType(BUILDING_BUILT);
        newEvent.add8bitsMessage(this->game.getPlayerID(playerName));
        newEvent.add16bitsMessage(this->buildingIDCount);
        newEvent.add8bitsMessage(ret);
        newEvent.add16bitsMessage(x);
        newEvent.add16bitsMessage(y);
        this->events.push_back(newEvent);
        this->buildingIDs[this->buildingIDCount] = playerName;
        this->buildingIDCount++;
    }
    return (ret != 0xFFFF);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Destruye un edificio.
 * */

void ActiveGame::destroyBuilding(std::string playerName, uint16_t id) {
    lock_t lock(this->m);
    game.destroyBuilding(playerName, id, this->events);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Mueve una unidad.
 * */

void ActiveGame::moveUnit(std::string playerName, uint16_t unitID, uint16_t x,
                          uint16_t y) {
    lock_t lock(this->m);
    this->game.moveUnit(playerName, unitID, coor_t(y, x));
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Ataca a una unidad.
 * */

void ActiveGame::attackUnit(uint16_t attacker, uint16_t attackedUnit) {
    lock_t lock(this->m);
    if (!this->hasUnit(attacker) || !this->hasUnit(attackedUnit))
        return;
    Unit* atta = this->game.getUnit(unitIDs[attacker], attacker);
    Unit* attad = this->game.getUnit(unitIDs[attackedUnit], attackedUnit);
    if (atta == nullptr || attad == nullptr)
        return;
    atta->attack(attad);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Ataca a un edificio.
 * */

void ActiveGame::attackBuilding(uint16_t attacker, uint16_t attackedBuilding) {
    lock_t lock(this->m);
    if (!this->hasUnit(attacker) || !this->hasBuilding(attackedBuilding))
        return;
    Unit* atta = this->game.getUnit(unitIDs[attacker], attacker);
    Building* attad = this->game.getBuilding(buildingIDs[attackedBuilding],
                                             attackedBuilding);
    if (atta == nullptr || attad == nullptr)
        return;
    atta->attack(attad);
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Desconecta a un jugador.
 * */

void ActiveGame::disconnect(std::string disconnected) {
    lock_t lock(this->m);
    this->game.disconnect(disconnected, this->events);
}

// std::list<std::string> ActiveGame::getPlayerNames() {
//     lock_t lock(this->m);
//     return this->game.getPlayerNames(this->gameMap);
// }

/*
 * Pre-condiciones: -
 * Post-condiciones: Destructor de la clase ActiveGame.
 * */

ActiveGame::~ActiveGame() {}
