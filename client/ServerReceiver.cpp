#include "ServerReceiver.h"
#include "SdlWindow.h"

#include <iostream>

ServerReceiver::ServerReceiver(ProtocolClient* protocol): protocolClient(protocol) {
	printf("prueba 1\n");
}

void ServerReceiver::run() {
	printf("hola!!! \n");
	//printf("prueba 5\n");
	this->receiveBackground();
}

void ServerReceiver::receiveBackground() {
	//Logica para recibir. Recibir todo de una. Ver como partir los mensajes. 
	printf("ok 1 \n");
	int height = 10;
	int width = 10;	
	std::cout << "voy a dibujar!!/n"; 
	printf("ok 2\n");
	SdlWindow sdlWindow(width, height, false, "DUNE 2000");
	printf("ok 3 \n");
	std::cout << "voy a dibujar0/n";
	GameView gameViewObj(sdlWindow); // aca esta el problema
	printf("ok 4\n");
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
	std::cout << "voy a dibujar/n"; //hasta aca no hay problemas 
	Drawer drawerThread(gameView);
	drawer = &drawerThread;
	drawer->start(); // aca esta el problema 
}

ServerReceiver::~ServerReceiver() {
	this->join();
}