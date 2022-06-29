#include <iomanip>
#include <sstream>
#include <cstdint>
#include <arpa/inet.h>
#include <vector>
#include <fstream>
#include <cstring>

#include "client_client.h"
#include "client_protocol.h"

#include <iostream>

/*
Pre-Condiciones: -
Post-Condiciones: Constructor de Protocolo.
*/

ProtocolClient::ProtocolClient():socket() {
}

/*
Pre-Condiciones: -
Post-Condiciones: Setea la conexion entre un cliente y un servidor.
*/

void ProtocolClient::setSktConnection(const char* name_host, const char* service_port) {
	this->socket.socketConnect(name_host, service_port);
}

/*
Pre-Condiciones: -
Post-Condiciones: (Serializacion) Pasa de un int a un uint16_t, pasandolo a BE. 
*/

uint16_t ProtocolClient::convert_to_uint16_with_endianess(int number) {
	uint16_t num_aux = htons((uint16_t) number);
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: (Serializacion) Pasa de un int a un uint8_t. 
*/

uint8_t ProtocolClient::convert_to_uint8(int number) {
	uint8_t num_aux = (uint8_t) number;
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Pasa de un uint8_t a un int. 
*/

int ProtocolClient::convert_from_uint8(uint8_t number){
	int num_aux = (int) number;
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Pasa de un uint16_t a un int, pasandolo a LE. 
*/

int ProtocolClient::convert_from_uint16_with_endianess(uint16_t number){
	int num_aux = ntohs((int) number);
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del protocolo.
*/

ProtocolClient::~ProtocolClient() {
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe un mensaje del servidor sobre la cantidad de elementos que
va a recibir el cliente.
*/

int ProtocolClient::receiveTwoBytes() {
	uint16_t count_convert = 0;
	socket.recvall(&count_convert,2);
	int count = convert_from_uint16_with_endianess(count_convert); 
	return count;
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe mensaje del servidor sobre si se pudo o no realizar una accion.
*/

int ProtocolClient::receiveOneByte() {
	uint8_t result = 0;
	socket.recvall(&result,1);
	int result_convert = convert_from_uint8(result);
	return result_convert;
}

/*
Pre-Condiciones: -
Post-Condiciones: Envia mensaje al servidor con el nombre del Usuario. 
*/

void ProtocolClient::sendUserName(std::string userName) {
	uint16_t nameSize = convert_to_uint16_with_endianess(userName.size());
	socket.sendall(&nameSize, 2);
	socket.sendall(&userName[0], userName.size());
}

void ProtocolClient::sendOperation(int operationNumber) {
	uint8_t operationNumberConvert = convert_to_uint8(operationNumber);
	socket.sendall(&operationNumberConvert, 1);
}

void ProtocolClient::sendCreateGameOperation(int operationNumber) {
	this->sendOperation(operationNumber);
}

void ProtocolClient::sendCreateGameInfo(std::string gameName, std::string mapName, int houseNumber) {
	uint8_t houseNumberConvert = convert_to_uint8(houseNumber);
	uint16_t nameSize = convert_to_uint16_with_endianess(gameName.size());
	uint16_t mapNameSize = convert_to_uint16_with_endianess(mapName.size());
	socket.sendall(&nameSize, 2);
	socket.sendall(&gameName[0], gameName.size());
	socket.sendall(&mapNameSize, 2);
	socket.sendall(&mapName[0], mapName.size());
	socket.sendall(&houseNumberConvert, 1);
}

void ProtocolClient::sendJoinGameOperation(int operationNumber, std::string gameName, int houseNumber) {
	this->sendOperation(operationNumber);
	uint8_t houseNumberConvert = convert_to_uint8(houseNumber);
	uint16_t gameNameSize = convert_to_uint16_with_endianess(gameName.size());
	socket.sendall(&gameNameSize, 2);
	socket.sendall(&gameName[0], gameName.size());
	socket.sendall(&houseNumberConvert, 1);
}

void ProtocolClient::sendListGamesOperation(int operationNumber) {
	this->sendOperation(operationNumber);
}

void ProtocolClient::sendListMapsOperation(int operationNumber) {
	this->sendOperation(operationNumber);
}

void ProtocolClient::recvListOfMaps(std::list<std::string>& list) {
	uint16_t numberOfMapsConvert = 0;
	socket.recvall(&numberOfMapsConvert, 2);
	int numberOfMaps = convert_from_uint16_with_endianess(numberOfMapsConvert);
	for(int i = 0; i < numberOfMaps; i++) {
		uint16_t nameSizeConvert = 0;
		socket.recvall(&nameSizeConvert, 2);
		int nameSize = convert_from_uint16_with_endianess(nameSizeConvert);
		std::string mapName;
		mapName.resize(nameSize);
		socket.recvall(&mapName[0], nameSize);
		list.push_back(mapName);
	}
}

void ProtocolClient::recvListOfGames(std::list <std::string>& list) {
	uint16_t numberOfGamesConvert = 0;
	socket.recvall(&numberOfGamesConvert, 2);
	int numberOfGames = convert_from_uint16_with_endianess(numberOfGamesConvert);
	for(int i = 0; i < numberOfGames; i++) {
		int numberPlayersInt = receiveOneByte();

		int numberRequiredInt = receiveOneByte();

		uint16_t nameSizeConvert = 0;
		socket.recvall(&nameSizeConvert, 2);
		int nameSize = convert_from_uint16_with_endianess(nameSizeConvert);
		std::string gameName;
		gameName.resize(nameSize);
		socket.recvall(&gameName[0], nameSize);

		list.push_back(gameName);
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: 
*/

void ProtocolClient::sendUnitConstructionPetition(int operation, int type) {
	this->sendOperation(operation);
	uint8_t unitType = convert_to_uint8(type);
	socket.sendall(&unitType, 1);
}

void ProtocolClient::sendOperationInfo(int operation, int type, int param1, int param2) {
	this->sendOperation(operation);
	uint8_t unitType = convert_to_uint8(type);
	socket.sendall(&unitType, 1);
	uint16_t parameter1 = convert_to_uint16_with_endianess(param1);
	uint16_t parameter2 = convert_to_uint16_with_endianess(param2);
	socket.sendall(&parameter1, 2);
	socket.sendall(&parameter2, 2);
}

void ProtocolClient::recvMap(int* width, int* height, std::vector<std::vector<uint8_t>>& map) {
	int rows = receiveTwoBytes();
	int cols = receiveTwoBytes();
	for (int i = 0; i < rows; i ++) {
		std::vector<uint8_t> row;
		row.resize(cols);
		socket.recvall(&row[0], cols);
		map.push_back(std::move(row));
	}
	*height = rows;
	*width = cols;
}

std::map<int, int> ProtocolClient::recvConstYards(std::map<int, std::tuple<int, int, int, bool>>& constYards,
												  std::string& clientName, int* clientId) {
	std::map<int, int> clientHouses;
	int playersAmount = receiveOneByte();
	for (int i = 0; i < playersAmount; i ++) {
		bool property = false;
		int nameSize = receiveTwoBytes();
		std::string name;
		name.resize(nameSize);
		socket.recvall(&name[0], nameSize);
		int x = receiveTwoBytes();
		int y = receiveTwoBytes();
		int house = receiveOneByte();
		if (name.compare(clientName) == 0) {
			*clientId = i;
			property = true;
		}
		clientHouses[i] = house;
		constYards[i] = std::make_tuple(x, y, house, property);
	}
	return clientHouses;
}

void ProtocolClient::recvUnits(std::map<int, std::tuple<int, int, int, int, int, bool>>& units, int clientId) {
	int playersAmount = receiveTwoBytes();
	
	for (int i = 0; i < playersAmount; i ++) {
		bool propiety = false;
		int playerId = receiveOneByte();
		int unitsAmount = receiveTwoBytes();

		if (clientId == playerId) propiety = true;

		for (int i = 0; i < unitsAmount; i ++) {
			int x = receiveTwoBytes() * 4;
			int y = receiveTwoBytes() * 4;
			int type = receiveOneByte();
			int direction = receiveOneByte();
			int unitId = receiveTwoBytes();
			units[unitId] = std::make_tuple(x, y, type, playerId, direction, propiety);
		}
	}
}

std::tuple<int, int, int, int, int, bool> ProtocolClient::recvBuildingInfo(int clientId) {
	int playerId = receiveOneByte();
	int buildingId = receiveTwoBytes();
	int buildingType = receiveOneByte();
	int x = receiveTwoBytes();
	int y = receiveTwoBytes();
	bool property = false;
	if (playerId == clientId) property = true;
	return std::make_tuple(x, y, playerId, buildingId, buildingType, property);
}

std::tuple<int, int, int, int> ProtocolClient::receiveAttackInfo() {
	int attackerId = receiveTwoBytes();
	int attackedId = receiveTwoBytes();
	int currentLife = receiveTwoBytes();
	int totalLife = receiveTwoBytes();
	return std::make_tuple(attackedId, attackedId, currentLife, totalLife);
}

void ProtocolClient::recvUnitStatus(std::vector<std::tuple<int, int, bool>>& unitsInConstruction, int clientId) {
	int unitsAmount = receiveTwoBytes();
	for (int i = 0; i < unitsAmount; i ++) {
		int playerId = receiveOneByte();
		int unitType = receiveOneByte();
		int constPercentage = receiveTwoBytes();
		bool propiety = false;
		if (clientId == playerId) propiety = true;
		unitsInConstruction.push_back(std::make_tuple(unitType, constPercentage, propiety));
	}
}

int ProtocolClient::recvStartGame() {
	return receiveOneByte();
}

int ProtocolClient::recvOperationResult() {
	return receiveOneByte();
}

int ProtocolClient::recvOperationNumber() {
	return receiveOneByte();
}
