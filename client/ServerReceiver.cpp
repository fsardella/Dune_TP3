#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>

#define SUCCESSFULL_OPERATION 0
#define FAILED_OPERATION 1
#define UNIT_BROADCAST 2
#define BUILDING_CONSTRUCTED 3
#define UNIT_ATTACKED 4
#define BUILDING_ATTACKED 5
#define GAME_LOST 6
#define GAME_WON 7
#define UNIT_UNDER_CONSTRUCTION 8

ServerReceiver::ServerReceiver(ProtocolClient* protocol,
							   GameView* gameViewObj,
							   std::string& clientName,
							   int* result)
: protocolClient(protocol),
  gameView(gameViewObj),
  clientName(clientName),
  result(result)
{}

void ServerReceiver::run() {
	try {
		this->receiveBackground();
		this->buildConstructionYards();
		gameView->setEnergy(0); //iria energy
		gameView->setMoney(0); //iria money
		gameView->buildUnit(100, 100, 0, 0, 0, 0, true); // borrar
		this->gameLoop();
	} catch(const ClosedSocketException& e) {
		std::cout << "el socket se cerro inesperadamente 2\n";
	}
	
}

void ServerReceiver::receiveBackground() {
	int width, height;
	std::vector<std::vector<uint8_t>> map;
	protocolClient->recvMap(&width, &height, map);
	gameView->buildMap(height, width, std::move(map));
}

void ServerReceiver::buildConstructionYards() {
	std::map<int, std::tuple<int, int, int, bool>> constYards;
	clientHouses = protocolClient->recvConstYards(constYards, clientName, &clientId);
	for (const auto& [key, value] : constYards) {
		// x y id type house property
		gameView->buildConstruction(std::get<0>(value), std::get<1>(value), key,
									0, std::get<3>(value), std::get<2>(value));
	}
}

void ServerReceiver::gameLoop() {
	while(gameView->isRunning()) {
		int operacion = protocolClient->recvOperationNumber();
		switch (operacion)
		{
		case SUCCESSFULL_OPERATION:
			// en gameView/mapView tener cola de eventos pendientes
			// llamar a mensaje successOperation (no creado) y eliminar el evento
			// mostrarlo en la interfaz
			break;
		case FAILED_OPERATION:
			// en gameView/mapView tener cola de eventos pendientes
			// llamar a mensaje failedOperation (no creado) y eliminar el evento
			// mostrarlo en la interfaz
			break;
		case UNIT_BROADCAST:
			this->receiveUnits();
			break;
		case BUILDING_CONSTRUCTED:
			this->receiveBuilding();
			break;
		case UNIT_ATTACKED:
			// dibujar destellos
			this->receiveUnitAttack();
			break;
		case BUILDING_ATTACKED:
			// dibujar destellos
			this->receiveBuildingAttack();
			break;
		case GAME_LOST:
			*result = 0;
			gameView->shutdown();
			break;
		case GAME_WON:
			*result = 1;
			gameView->shutdown();
			break;
		case UNIT_UNDER_CONSTRUCTION:
			// imagen quieta y la updateamos con el porcentaje aca
			break;
		}
		// int money = protocolClient->recvMoney();
		// int energy = protocolClient->recvEnergy();
	}
}

void ServerReceiver::receiveUnits() {
	std::map<int, std::tuple<int, int, int, int, int, bool>> units;
	protocolClient->recvUnits(units, clientId);
	gameView->buildUnits(units);
}

void ServerReceiver::receiveBuilding() {
	std::tuple<int, int, int, int, int, bool> buildingInfo = protocolClient->recvBuildingInfo(clientId);
	gameView->buildConstruction(std::get<0>(buildingInfo), std::get<1>(buildingInfo),
								std::get<3>(buildingInfo), std::get<4>(buildingInfo),
								std::get<5>(buildingInfo), clientHouses[std::get<2>(buildingInfo)]);
}

void ServerReceiver::receiveUnitAttack() {
	// atancante atacado vidaactual vidatotal
	std::tuple<int, int, int, int> attackInfo = protocolClient->receiveAttackInfo();
	gameView->unitAttack(std::get<0>(attackInfo), std::get<1>(attackInfo),
						 std::get<2>(attackInfo), std::get<3>(attackInfo));
}

void ServerReceiver::receiveBuildingAttack() {
	// atancante atacado vidaactual vidatotal
	std::tuple<int, int, int, int> attackInfo = protocolClient->receiveAttackInfo();
	gameView->buildingAttack(std::get<0>(attackInfo), std::get<1>(attackInfo),
						 	 std::get<2>(attackInfo), std::get<3>(attackInfo));
}

ServerReceiver::~ServerReceiver() {
}