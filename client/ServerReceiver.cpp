#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <utility>
#include <vector>
#include <tuple>

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
#define BUILDING_DESTROYED 12

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

void ServerReceiver::run() {
    try {
        this->receiveBackground();
        this->buildConstructionYards();
        gameView->setEnergy(0);  // iria energy
        gameView->setMoney(0);  // iria money

        gameView->updateSpecie(0, 0, 5);

        // gameView->buildUnit(100, 100, 0, 0, 0, 5, true); // BORRAR
        // gameView->buildUnit(110, 100, 2, 2, 0, 5, true); // BORRAR
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

void ServerReceiver::receiveBackground() {
    int width, height;
    std::vector<std::vector<uint8_t>> map;
    protocolClient->recvMap(width, height, map);
    gameView->buildMap(height, width, std::move(map));
}

void ServerReceiver::buildConstructionYards() {
    std::map<int, std::tuple<int, int, int, int, bool>> constYards;
    clientHouses = protocolClient->recvConstYards(constYards, clientName,
                                                  clientId);
    for (const auto& [key, value] : constYards) {
        // x y id type house property
        gameView->buildConstruction(std::get<0>(value), std::get<1>(value),
                                    std::get<2>(value), key, 11,
                                    std::get<4>(value), std::get<3>(value));
    }
}

void ServerReceiver::gameLoop() {
    while (gameView->isRunning()) {
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
            gameView->shutdown();
            break;
        case GAME_WON:
            result = 1;
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
        case BUILDING_DESTROYED:
            this->receiveDestroyedBuilding();
            break;
        }
    }
}

void ServerReceiver::receiveUnits() {
    std::map<int, std::tuple<int, int, int, int, int, bool>> units;
    int money, energy;
    protocolClient->recvUnits(units, clientId, money, energy);
    gameView->setEnergy(energy);
    gameView->setMoney(money);
    gameView->buildUnits(units);
}

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

void ServerReceiver::receiveUnitAttack() {
    std::tuple<int, int, int, int> attackInfo =
            protocolClient->receiveAttackInfo();
    gameView->unitAttack(std::get<0>(attackInfo),
                         std::get<1>(attackInfo),
                         std::get<2>(attackInfo),
                         std::get<3>(attackInfo));
}

void ServerReceiver::receiveBuildingAttack() {
    std::tuple<int, int, int, int> attackInfo =
            protocolClient->receiveAttackInfo();
    gameView->buildingAttack(std::get<0>(attackInfo),
                             std::get<1>(attackInfo),
                             std::get<2>(attackInfo),
                             std::get<3>(attackInfo));
}

void ServerReceiver::receiveUnitProgress() {
    std::vector<std::tuple<int, int>> unitProgress;
    protocolClient->recvUnitsProgress(unitProgress, clientId);
    for (std::tuple<int, int>& unit : unitProgress) {
        gameView->updateProgress(std::get<0>(unit), std::get<1>(unit));
    }
}

void ServerReceiver::receiveBuildingProgress() {
    std::vector<int> buildingProgress;
    protocolClient->recvBuildingProgress(buildingProgress);
    gameView->updateProgress(buildingProgress.at(0), buildingProgress.at(1));
}

void ServerReceiver::receiveWormInfo() {
    int x, y;
    std::vector<int> deadId;
    protocolClient->recvWormAttack(x, y, deadId);
    gameView->wormAttack(x, y, deadId);
}

void ServerReceiver::receiveRefinementInfo() {
    std::vector<std::tuple<int, int, int>> species;
    protocolClient->recvRefinementInfo(species);
    for (std::tuple<int, int, int>& specie : species) {
        gameView->updateSpecie(std::get<0>(specie), std::get<1>(specie),
                               std::get<2>(specie));
    }
}

void ServerReceiver::receiveDestroyedBuilding() {
    int id = protocolClient->receiveDestroyedBuilding();
    gameView->destroyBuilding(id);
}

ServerReceiver::~ServerReceiver() {
}
