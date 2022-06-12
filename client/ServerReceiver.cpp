#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>

ServerReceiver::ServerReceiver(ProtocolClient* protocol): protocolClient(protocol) {
}

void ServerReceiver::run() {
	this->receiveBackground();
}

void ServerReceiver::receiveBackground() {
	//Logica para recibir. Recibir todo de una. Ver como partir los mensajes. 
	int height = 600;
	int width = 800;
	SdlWindow sdlWindow(width, height, false, "DUNE 2000");
	GameView gameViewObj(sdlWindow);
	gameView = &gameViewObj;
	std::vector<std::vector<int>> map {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	gameView->buildMap(10, 10, map);
	Drawer drawerThread(gameView);
	drawer = &drawerThread;
	drawer->start();
}

ServerReceiver::~ServerReceiver() {
	this->join();
}
