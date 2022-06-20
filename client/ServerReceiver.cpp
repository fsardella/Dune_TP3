#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>

ServerReceiver::ServerReceiver(ProtocolClient* protocol, GameView* gameViewObj): protocolClient(protocol), gameView(gameViewObj) {
}

void ServerReceiver::run() {
	this->receiveBackground();
	//while(gameView->isRunning()) {
		// std::map<int, std::tuple<int, int, int, bool>> units;
		// protocolClient->recvUnits(units);
		// gameView->buildUnits(units);
		// int money = protocolClient->recvMoney();
		// int energy = protocolClient->recvEnergy();
		gameView->buildUnit(32, 32, 1, 1);
		gameView->setEnergy(0); //iria energy
		gameView->setMoney(0); //iria money
	//}
}

void ServerReceiver::receiveBackground() {
	// int width, int height;
	// std::vector<std::vector<int>> map;
	// protocolClient->recvMap(&width, &height, map);

	std::vector<std::vector<int>> map;
	for (int i = 0; i < 100; i ++) {
		std::vector<int> row;
		for (int j = 0; j < 100; j ++) {
			row.push_back(0);
		}
		map.push_back(row);
	}
	// gameView->setSize(10*32, 10*32);
	// gameView->setSize(100, 100);
	gameView->buildMap(100, 100, map);
}

ServerReceiver::~ServerReceiver() {
}