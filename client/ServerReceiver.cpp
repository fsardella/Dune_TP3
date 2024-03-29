#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <utility>

#define SUCCESSFULL_OPERATION 0
#define FAILED_OPERATION 1
#define UNIT_BROADCAST 2
#define BUILDING_CONSTRUCTED 3
#define UNIT_ATTACKED 4
#define BUILDING_ATTACKED 5
#define GAME_LOST 6
#define GAME_WON 7
#define UNIT_UNDER_CONSTRUCTION 8
#define BUILDING_UNDER_CONSTRUCTION 9
#define WORM 10
#define REFINEMENT 11
#define CONST_YARD_ID 11

/*
Pre-Condiciones: Constructor de Server Receiver.
Post-Condiciones: -
*/

ServerReceiver::ServerReceiver(ProtocolClient* protocol,
                               GameView* gameViewObj,
                               std::string& clientName,
                               int& result)
: protocolClient(protocol),
  gameView(gameViewObj),
  clientName(clientName),
  clientId(0),
  result(result)
{}

/*
Pre-Condiciones: Se lanza el server receiver.
Post-Condiciones: -
*/

void ServerReceiver::run() {
    try {
        this->receiveBackground();
        this->buildConstructionYards();
        // gameView->setEnergy(0);  // iria energy
        // gameView->setMoney(0);  // iria money

        // gameView->updateSpecie(0, 0, 5);

        // std::this_thread::sleep_for (std::chrono::seconds(3));

        // // // std::cout << "creo unidades\n";
        // gameView->buildUnit(110, 100, 16, 5, 0, 8, false); // BORRAR
        // gameView->unitAttack(-1, 16, 0, 80);
        // gameView->buildUnit(110, 100, 16, 9, 0, 8, false); // BORRAR
        // gameView->buildUnit(150, 200, 17, 0, 0, 3, true); // BORRAR
        // std::this_thread::sleep_for (std::chrono::seconds(2));
        // gameView->buildUnit(150, 200, 17, 0, 1, 3, false); // BORRAR

        // // gameView->wormAttack(200, 150);
        // // gameView->unitAttack(-1, 17, 0, 80);

        // std::cout << "termino de crear unidades\n";
        // gameView->unitAttack(16, 17, 80, 80, 0);
        // std::cout << "empieza el segundo\n";
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // std::cout << "termina el segundo\n";
        // // gameView->buildUnit(200, 150, 17, 0, 0, 3, false);
        // gameView->unitAttack(16, 17, 60, 80, 1);
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // // gameView->buildUnit(200, 150, 17, 0, 0, 3, false);
        // gameView->unitAttack(16, 17, 40, 80, 0);
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // // gameView->buildUnit(200, 150, 17, 0, 0, 3, false);
        // gameView->unitAttack(16, 17, 0, 80, 1);
        // // gameView->buildUnit(200, 150, 17, 0, 0, 3, false);
        // std::this_thread::sleep_for (std::chrono::seconds(1));

        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // std::cout << "lo intento creat\n";
        // gameView->buildConstruction(300, 150, 0, 18, 11, true, 0);

        // gameView->buildingAttack(16, 18, 80, 80);
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // gameView->buildingAttack(16, 18, 60, 80);
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // gameView->buildingAttack(16, 18, 40, 80);
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // gameView->buildingAttack(16, 18, 0, 80);

        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // std::vector<int> deaths;
        // deaths.push_back(0);
        // deaths.push_back(2);
        // gameView->wormAttack(100, 100, deaths);

        // gameView->buildUnit(100, 200, 4, 5, 0, 5, true); // BORRAR
        // gameView->buildUnit(100, 300, 5, 7, 0, 5, true); // BORRAR
        // gameView->buildUnit(150, 150, 1, 9, 1, 5, false); // BORRAR
        // gameView->buildUnit(200, 100, 2, 10, 2, 5, false); // BORRAR

        // gameView->buildConstruction(300, 100, 0, 3, 12, true, 0);

        // gameView->updateProgress(11, 0);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->updateProgress(11, 20);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->updateProgress(11, 50);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->updateProgress(11, 60);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->updateProgress(11, 100);

        // ATAQUE A UNIDAD

        /* gameView->buildUnit(200, 100, 1, 10, 1, 3, false); // BORRAR
        gameView->unitAttack(0, 1, 80, 80);
        std::this_thread::sleep_for (std::chrono::seconds(3));
        gameView->unitAttack(0, 1, 60, 80);
        std::this_thread::sleep_for (std::chrono::seconds(3));
        gameView->unitAttack(0, 1, 40, 80);
        std::this_thread::sleep_for (std::chrono::seconds(3));
        gameView->unitAttack(0, 1, 0, 80);
        std::this_thread::sleep_for (std::chrono::seconds(3));

        gameView->buildUnit(100, 150, 2, 5, 0, 5, true); // BORRAR
        gameView->buildUnit(200, 150, 4, 9, 1, 3, false); // BORRAR
        gameView->unitAttack(2, 4, 80, 80);
        std::this_thread::sleep_for (std::chrono::seconds(3));
        gameView->unitAttack(2, 4, 60, 80);
        std::this_thread::sleep_for (std::chrono::seconds(3));
        gameView->unitAttack(2, 4, 40, 80);
        std::this_thread::sleep_for (std::chrono::seconds(3));
        gameView->unitAttack(2, 4, 0, 80); */

        // ATAQUE A EDIFICIO
        // gameView->buildConstruction(300, 100, 0, 3, 12, true, 2);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->destroyBuilding(3);

        // gameView->buildingAttack(0, 3, 80, 80);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->buildingAttack(0, 3, 60, 80);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->buildingAttack(0, 3, 40, 80);
        // std::this_thread::sleep_for (std::chrono::seconds(3));
        // gameView->buildingAttack(0, 3, 0, 80);


        // gameView->buildUnit(150, 100, 2, 0, 4, 5, false); // BORRAR


        // gameView->buildUnit(150, 150, 1, 9, 1, 5, false);

        /* gameView->buildConstruction(450, 100, 1, 4, 12, true, 0);

         std::this_thread::sleep_for (std::chrono::seconds(3));
         gameView->buildingAttack(2, 4, 80, 80);
         std::this_thread::sleep_for (std::chrono::seconds(3));
         gameView->buildingAttack(2, 4, 60, 80);
         std::this_thread::sleep_for (std::chrono::seconds(3));
         gameView->buildingAttack(2, 4, 40, 80);
         std::this_thread::sleep_for (std::chrono::seconds(3));
         gameView->buildingAttack(2, 4, 0, 80);*/

        // MOVIMIENTO
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // gameView->buildUnit(110, 100, 0, 0, 0, 5, true); // BORRAR
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // gameView->buildUnit(120, 100, 0, 0, 0, 5, true); // BORRAR
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // gameView->buildUnit(130, 100, 0, 0, 0, 5, true); // BORRAR
        // std::this_thread::sleep_for (std::chrono::seconds(1));
        // gameView->buildUnit(300, 100, 0, 0, 0, 5, true); // BORRAR
        // std::this_thread::sleep_for (std::chrono::seconds(1));

        // VARIAS CONSTRUCCIONES
        // gameView->buildConstruction(400, 400, 4, 18, true, 0);
        // gameView->buildConstruction(100, 500, 6, 18, true, 2);
        // gameView->buildConstruction(500, 100, 5, 16, true, 0);
        this->gameLoop();
    } catch(const ClosedSocketException& e) {
        std::cout << "el socket se cerro inesperadamente 2\n";
    }
}

/*
Pre-Condiciones: Recibe la información para crear el mapa.
Post-Condiciones: -
*/

void ServerReceiver::receiveBackground() {
    int width, height;
    std::vector<std::vector<uint8_t>> map;
    protocolClient->recvMap(width, height, map);
    gameView->buildMap(height, width, std::move(map));
}


/*
Pre-Condiciones: Recibe la información para crear un centro de construcción.
Post-Condiciones: -
*/

void ServerReceiver::buildConstructionYards() {
    std::map<int, std::tuple<int, int, int, int, bool>> constYards;
    clientHouses = protocolClient->recvConstYards(constYards, clientName,
                                                  clientId);
    for (const auto& [key, value] : constYards) {
        // x y id type house property
        gameView->buildConstruction(std::get<0>(value), std::get<1>(value),
                                    std::get<2>(value), key, CONST_YARD_ID,
                                    std::get<4>(value), std::get<3>(value));
    }
}

/*
Pre-Condiciones: Loop del server receiver.
Post-Condiciones: -
*/

void ServerReceiver::gameLoop() {
    while (gameView->isRunning()) {
        protocolClient->receiveTwoBytes();
        int operation = protocolClient->recvOperationNumber();
        switch (operation) {
        case SUCCESSFULL_OPERATION:
            // no utilizado evitando message responce
            break;
        case FAILED_OPERATION:
            // no utilizado evitando message responce
            break;
        case UNIT_BROADCAST:
            this->receiveUnits();
            break;
        case BUILDING_CONSTRUCTED:
            this->receiveBuilding();
            break;
        case UNIT_ATTACKED:
            this->receiveUnitAttack();
            break;
        case BUILDING_ATTACKED:
            this->receiveBuildingAttack();
            break;
        case GAME_LOST:
            result = 0;
            gameView->playLostSound();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            gameView->shutdown();
            break;
        case GAME_WON:
            result = 1;
            gameView->playWinSound();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            gameView->shutdown();
            break;
        case UNIT_UNDER_CONSTRUCTION:
            this->receiveUnitProgress();
            break;
        case BUILDING_UNDER_CONSTRUCTION:
            this->receiveBuildingProgress();
            break;
        case WORM:
            this->receiveWormInfo();
            break;
        case REFINEMENT:
            this->receiveRefinementInfo();
            break;
        }
    }
}


/*
Pre-Condiciones: Recibe la información para crear unidades.
Post-Condiciones: -
*/

void ServerReceiver::receiveUnits() {
    std::map<int, std::tuple<int, int, int, int, int, bool>> units;
    int money, energy;
    protocolClient->recvUnits(units, clientId, money, energy);
    gameView->setEnergy(energy);
    gameView->setMoney(money);
    gameView->buildUnits(units);
}

/*
Pre-Condiciones: Recibe la información para crear un edificio.
Post-Condiciones: -
*/

void ServerReceiver::receiveBuilding() {
    std::tuple<int, int, int, int, int, bool> buildingInfo =
                protocolClient->recvBuildingInfo(clientId);
    gameView->buildConstruction(std::get<0>(buildingInfo),
                                std::get<1>(buildingInfo),
                                std::get<2>(buildingInfo),
                                std::get<3>(buildingInfo),
                                std::get<4>(buildingInfo),
                                std::get<5>(buildingInfo),
                                clientHouses[std::get<2>(buildingInfo)]);
}

/*
Pre-Condiciones: Recibe el ataque hacia una unidad.
Post-Condiciones: -
*/

void ServerReceiver::receiveUnitAttack() {
    std::tuple<int, int, int, int, int> attackInfo =
            protocolClient->receiveAttackInfo();
    gameView->unitAttack(std::get<0>(attackInfo),
                         std::get<1>(attackInfo),
                         std::get<2>(attackInfo),
                         std::get<3>(attackInfo),
                         std::get<4>(attackInfo));
}

/*
Pre-Condiciones: Recibe el ataque hacia un edificio.
Post-Condiciones: -
*/

void ServerReceiver::receiveBuildingAttack() {
    std::tuple<int, int, int, int, int> attackInfo =
            protocolClient->receiveAttackInfo();
    gameView->buildingAttack(std::get<0>(attackInfo),
                             std::get<1>(attackInfo),
                             std::get<2>(attackInfo),
                             std::get<3>(attackInfo),
                             std::get<4>(attackInfo));
}

/*
Pre-Condiciones: -
Post-Condiciones: Devuelve verdadero si la unidad en construcción que antes
estaba en construcción ahora también lo está, falso en caso contrario.
*/

bool ServerReceiver::checkIsStillUnderConstruction(int previousUnit,
                            std::vector<std::tuple<int, int>> unitProgress) {
    for (std::tuple<int, int>& unit : unitProgress) {
        if (std::get<0>(unit) == previousUnit) return true;
    }
    return false;
}

/*
Pre-Condiciones: Recibe el progreso de la unidad en entrenamiento.
Post-Condiciones: -
*/

void ServerReceiver::receiveUnitProgress() {
    std::vector<std::tuple<int, int>> unitProgress;
    protocolClient->recvUnitsProgress(unitProgress, clientId);
    for (std::tuple<int, int>& unit : unitProgress) {
        gameView->updateProgress(std::get<0>(unit), std::get<1>(unit));
    }
    for (int& previousUnit : unitsUnderConstruction) {
        if (checkIsStillUnderConstruction(previousUnit, unitProgress)) {
            continue;
        }
        gameView->stopConstruction(previousUnit);
    }
    unitsUnderConstruction.clear();
    for (std::tuple<int, int>& unit : unitProgress) {
        unitsUnderConstruction.push_back(std::get<0>(unit));
    }
}

/*
Pre-Condiciones: Recibe el progreso del edificio en construcción.
Post-Condiciones: -
*/

void ServerReceiver::receiveBuildingProgress() {
    std::vector<int> buildingProgress;
    protocolClient->recvBuildingProgress(buildingProgress);
    gameView->updateProgress(buildingProgress.at(0), buildingProgress.at(1));
}

/*
Pre-Condiciones: Recibe información del gusano de arena.
Post-Condiciones: -
*/

void ServerReceiver::receiveWormInfo() {
    int x, y;
    // std::vector<int> deadId;
    protocolClient->recvWormAttack(x, y);
    gameView->wormAttack(x, y);
}

/*
Pre-Condiciones: Recibe que información de las refinerías.
Post-Condiciones: -
*/

void ServerReceiver::receiveRefinementInfo() {
    bool newGame = false;
    if (spices.empty()) newGame = true;
    std::vector<std::tuple<int, int, int>> species;
    protocolClient->recvRefinementInfo(species, spices);

    for (std::tuple<int, int, int>& specie : species) {
        gameView->updateSpecie(std::get<0>(specie), std::get<1>(specie),
                                std::get<2>(specie));
    }
    std::vector<std::tuple<int, int>> toDelete;
    for (auto& [key, value] : spices) {
        if (!spices.at(key) && !newGame) {
            gameView->updateSpecie(std::get<0>(key), std::get<1>(key),
                                   0);
            toDelete.push_back(std::make_tuple(std::get<0>(key),
                                               std::get<1>(key)));
        }
        spices[key] = false;
    }

    for (std::tuple<int, int>& deletePos : toDelete) {
        spices.erase(std::make_tuple(std::get<0>(deletePos),
                                     std::get<1>(deletePos)));
    }
}

/*
Pre-Condiciones: Destructor de Server Receiver.
Post-Condiciones: -
*/

ServerReceiver::~ServerReceiver() {
}
