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
			std::map<std::tuple<int, int>, std::tuple<int, int, bool>> units;
			protocolClient->recvUnits(units);
			gameView->buildUnits(units);
			// int money = protocolClient->recvMoney();
			// int energy = protocolClient->recvEnergy();
		}
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

ServerReceiver::~ServerReceiver() {
}