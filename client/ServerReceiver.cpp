#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>

ServerReceiver::ServerReceiver(ProtocolClient* protocol, GameView* gameViewObj): protocolClient(protocol), gameView(gameViewObj) {
}

void ServerReceiver::run() {
	try {
		this->receiveBackground();
		gameView->setEnergy(0); //iria energy
		gameView->setMoney(0); //iria money
		while(gameView->isRunning()) {
			std::map<int, std::tuple<int, int, int, bool>> units;
			protocolClient->recvUnits(units);
			gameView->buildUnits(units);
			// int money = protocolClient->recvMoney();
			// int energy = protocolClient->recvEnergy();
			// gameView->buildUnit(0, 0, 1, 0, 1, true, 0);

		}
	} catch(const ClosedSocketException& e) {
		std::cout << "el socket se cerro inesperadamente 2\n";
	}
	
}

void ServerReceiver::receiveBackground() {
	int width, height;
	std::vector<std::vector<uint8_t>> map;
	protocolClient->recvMap(&width, &height, map);

	// std::vector<std::vector<int>> map;
	// for (int i = 0; i < 100; i ++) {
	// 	std::vector<int> row;
	// 	for (int j = 0; j < 100; j ++) {
	// 		row.push_back(0);
	// 	}
	// 	map.push_back(row);
	// }

	gameView->buildMap(height, width, std::move(map));
}

ServerReceiver::~ServerReceiver() {
}