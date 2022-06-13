#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>

ServerReceiver::ServerReceiver(ProtocolClient* protocol, GameView* gameViewObj): protocolClient(protocol), gameView(gameViewObj) {
}

void ServerReceiver::run() {
	this->receiveBackground();
	//while(gameView->isRunning()) {
		//protocolClient->recvStatus();
		gameView->buildUnit(8, 8, "trike");
	//}
}

void ServerReceiver::receiveBackground() {
	std::vector<std::vector<int>> map {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	gameView->setSize(10*32, 10*32);
	gameView->buildMap(10, 10, map);
}

ServerReceiver::~ServerReceiver() {
}