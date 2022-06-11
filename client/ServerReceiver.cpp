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
	int height = 10;
	int width = 10;	
	std::cout << "voy a dibujar!!/n"; 
	SdlWindow sdlWindow(width, height, false, "DUNE 2000");
	std::cout << "voy a dibujar0/n";
	GameView gameViewObj(sdlWindow);
	std::cout << "voy a dibujar3/n";
	gameView = &gameViewObj;
	std::cout << "voy a dibujar4/n";
	std::vector<std::vector<int>> map {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	std::cout << "voy a dibujar5/n";
	gameView->buildMap(height, width, map);
	std::cout << "voy a dibujar/n";
	Drawer drawerThread(gameView);
	drawer = &drawerThread;
	drawer->start();
}

ServerReceiver::~ServerReceiver() {
	drawer->join();
}