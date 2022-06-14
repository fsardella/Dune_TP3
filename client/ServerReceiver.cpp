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
		gameView->buildUnit(8, 8, "trike", 1);
	//}
}

void ServerReceiver::receiveBackground() {
	// int width, int height;
	// std::vector<std::vector<int>> map;
	// protocolClient->recvMap(&width, &height, map);

	std::vector<std::vector<int>> map {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	gameView->setSize(10*32, 10*32);
	// gameView->setSize(100, 100);
	gameView->buildMap(10, 10, map);
}

ServerReceiver::~ServerReceiver() {
}