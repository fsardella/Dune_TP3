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
		gameView->buildUnit(0, 0, 1, 1);
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