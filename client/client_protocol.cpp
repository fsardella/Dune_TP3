#include <iostream>
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

uint16_t ProtocolClient::convert_to_uint16_with_endianess(int number){
	int num_aux = htons((uint16_t) number);
	return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: (Serializacion) Pasa de un int a un uint8_t. 
*/

uint8_t ProtocolClient::convert_to_uint8(int number){
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
Post-Condiciones: Envia mensaje al servidor para poder listar una partida con toda su información. 
*/

void ProtocolClient::send_msg_listar() {
    uint8_t listar_convert = convert_to_uint8(2);
	socket.sendall(&listar_convert, 1);
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe mensaje del servidor sobre el nombre del juego.
*/

std::string ProtocolClient::recieve_msg_game_name(int bytes) {
	std::vector<char> vector(bytes);
	for(int i = 0 ; i < bytes ; i++) {
		socket.recvall(&vector[i], 1);
	}
	std::string game_name(vector.begin(),vector.end());
	return game_name;
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe un mensaje del servidor sobre la cantidad de elementos que
va a recibir el cliente.
*/

int ProtocolClient::recieve_msg_count() {
	uint16_t count_convert = 0;
	socket.recvall(&count_convert,2);
	int count = convert_from_uint16_with_endianess(count_convert); 
	return count;
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe un mensaje del servidor para poder listar una partida 
con toda su información. 
*/

void ProtocolClient::recieve_msg_listar(uint8_t* current_convert, uint8_t* required_convert,
	std::string* game_name_convert) {
	uint16_t game_name_len_convert = 0;
	socket.recvall(current_convert,1);
	socket.recvall(required_convert,1);
	socket.recvall(&game_name_len_convert,2);
	int game_name_len = convert_from_uint16_with_endianess(game_name_len_convert);
	*game_name_convert = recieve_msg_game_name(game_name_len);
}

/*
Pre-Condiciones: -
Post-Condiciones: Envia mensaje al servidor para poder crear una partida. 
*/

void ProtocolClient::send_msg_crear(int house, int num_players,
	std::string& game_name) {
    uint8_t crear_convert = convert_to_uint8(3);
	socket.sendall(&crear_convert, 1);

	uint8_t house_convert = convert_to_uint8(house);
	socket.sendall(&house_convert, 1);

	uint8_t required_convert = convert_to_uint8(num_players);
	socket.sendall(&required_convert, 1);
	
	int num_bytes = game_name.length();
	uint16_t num_bytes_convert = convert_to_uint16_with_endianess(num_bytes);
	socket.sendall(&num_bytes_convert, 2);
	
	for(int i = 0 ; i < num_bytes ; i++) {
		socket.sendall(&game_name.at(i), 1);
	}
}

/*
Pre-Condiciones: -
Post-Condiciones: Recibe mensaje del servidor sobre si se pudo o no realizar una accion.
*/

int ProtocolClient::recieve_msg_result() {
	uint8_t result = 0;
	socket.recvall(&result,1);
	int result_convert = convert_from_uint8(result);
	return result_convert;
}

/*
Pre-Condiciones: -
Post-Condiciones: Envia mensaje al servidor para poder unirse a una partida. 
*/

void ProtocolClient::send_msg_unirse(int house, std::string& game_name) {
    uint8_t unirse_convert = convert_to_uint8(1);
	socket.sendall(&unirse_convert, 1);
	uint8_t house_convert = convert_to_uint8(house);
	socket.sendall(&house_convert, 1);
	int num_bytes = game_name.length();
	uint16_t num_bytes_convert = convert_to_uint16_with_endianess(num_bytes);
	socket.sendall(&num_bytes_convert, 2);
	for(int i = 0 ; i < num_bytes ; i++) {
		socket.sendall(&game_name.at(i), 1);
	}
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
	//Aca tambien se le pasaria toda la informacion necesaria para crear el Game.
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
	//Aca tambien se le pasaria toda la informacion necesaria para joinearse a un Game.
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
	std::cout << "cant de mapas " << numberOfMaps << std::endl;
	for(int i = 0; i < numberOfMaps; i++) {
		uint16_t nameSizeConvert = 0;
		socket.recvall(&nameSizeConvert, 2);
		int nameSize = convert_from_uint16_with_endianess(nameSizeConvert);
		std::cout << nameSize << std::endl;
		std::string mapName;
		mapName.resize(nameSize);
		socket.recvall(&mapName[0], nameSize);
		std::cout << mapName << std::endl;
		list.push_back(mapName);
	}
}

void ProtocolClient::recvListOfGames(std::list <std::string>& list) {
	uint16_t numberOfGamesConvert = 0;
	socket.recvall(&numberOfGamesConvert, 2);
	int numberOfGames = convert_from_uint16_with_endianess(numberOfGamesConvert);
	std::cout << "nomber of games " << numberOfGames << std::endl;
	for(int i = 0; i < numberOfGames; i++) {
		int numberPlayersInt = recieve_msg_result();
		std::cout << "players " << numberPlayersInt << std::endl;

		int numberRequiredInt = recieve_msg_result();
		std::cout << "players " << numberRequiredInt << std::endl;

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

void ProtocolClient::sendUnitConstructionPetition(int x, int y, int type) {
	//serializacion
	this->sendOperation(BUILD_UNIT);
	uint16_t posX = convert_to_uint16_with_endianess(x);
	uint16_t posY = convert_to_uint16_with_endianess(y);
	uint8_t unitType = convert_to_uint8(type);
	socket.sendall(&posX, 2);
	socket.sendall(&posY, 2);
	socket.sendall(&unitType, 1);
}

void ProtocolClient::recvMap(int* width, int* height, std::vector<std::vector<uint8_t>>& map) {
	int rows = recieve_msg_count(); // mejorar nombre de metodo
	int cols = recieve_msg_count(); // mejorar nombre de metodo
	std::cout << "rows " <<  rows << std::endl;
	std::cout << "cols " <<  cols << std::endl;
	for (int i = 0; i < rows; i ++) {
		std::vector<uint8_t> row;
		row.resize(cols);
		socket.recvall(&row[0], cols);

		// for (int j = 0; j < cols; j ++) {
		// 	int tile = recieve_msg_count();
		// 	// std::cout << "tile " << tile << std::endl;
		// 	row.push_back(tile);
		// }

		map.push_back(std::move(row));
	}
	*height = rows;
	*width = cols;
}

void ProtocolClient::recvUnits(std::map<int, std::tuple<int, int, int, bool>>& units) {
	int totalAmount = recieve_msg_count(); // cambiar nombres a todos los metodos

	int clientAmount = recieve_msg_count();
	int clientHouse = recieve_msg_result();

	for (int i = 0; i < clientAmount; i ++) {
		int x = recieve_msg_count() * 4;
		int y = recieve_msg_count() * 4;
		int type = recieve_msg_result();
		units[type] = std::make_tuple(x, y, clientHouse, true);
	}

	int othersAmount = 0;
	for (int i = clientAmount; i < totalAmount; i += othersAmount) {
		othersAmount = recieve_msg_count();
		int otherHouse = recieve_msg_result();
		for (int j = 0; j < othersAmount; j ++) {
			int otherX = recieve_msg_count() * 4;
			int otherY = recieve_msg_count() * 4;
			int otherType = recieve_msg_result();
			units[otherType] = std::make_tuple(otherX, otherY, otherHouse, false);
		}
	}
}

int ProtocolClient::recvStartGame() {
	return recieve_msg_result();
}

int ProtocolClient::recvOperationResult() {
	return 	recieve_msg_result();
}
