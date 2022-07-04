#include "client_protocol.h"
#include "client_client.h"
#include <arpa/inet.h>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <cstring>
#include <utility>

#include <iostream>

#define ONE_BYTE 1
#define TWO_BYTES 2
#define FOUR_BYTES 4

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

void ProtocolClient::setSktConnection(const char* name_host,
                                      const char* service_port) {
    this->socket.socketConnect(name_host, service_port);
}

/*
Pre-Condiciones: Cierra el socket.
Post-Condiciones: -
*/

void ProtocolClient::closeCommunication() {
    this->socket.shutdown(2);
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

int ProtocolClient::convert_from_uint8(uint8_t number) {
    int num_aux = static_cast<int>(number);
    return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Pasa de un uint16_t a un int, pasandolo a LE. 
*/

int ProtocolClient::convert_from_uint16_with_endianess(uint16_t number) {
    int num_aux = ntohs(static_cast<int>(number));
    return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Pasa de un uint32_t a un int, pasandolo a LE. 
*/

int ProtocolClient::convert_from_uint32_with_endianess(uint32_t number) {
    int num_aux = ntohl(static_cast<int>(number));
    return num_aux;
}

/*
Pre-Condiciones: -
Post-Condiciones: Destructor del protocolo.
*/

ProtocolClient::~ProtocolClient() {
}

/*
Pre-Condiciones: Recibe mensaje del servidor sobre si se pudo o
no realizar una accion.
Post-Condiciones: -
*/

int ProtocolClient::receiveOneByte() {
    uint8_t result = 0;
    socket.recvall(&result, ONE_BYTE);
    int result_convert = convert_from_uint8(result);
    return result_convert;
}


/*
Pre-Condiciones: Recibe un mensaje del servidor sobre la cantidad
de elementos que va a recibir el cliente.
Post-Condiciones: -
*/

int ProtocolClient::receiveTwoBytes() {
    uint16_t result = 0;
    socket.recvall(&result, TWO_BYTES);
    if (result == 0xFFFF) return -1;
    int result_convert = convert_from_uint16_with_endianess(result);
    return result_convert;
}

/*
Pre-Condiciones: Recibe un mensaje del servidor sobre la cantidad de
elementos que va a recibir el cliente.
Post-Condiciones: -
*/

int ProtocolClient::receiveFourBytes() {
    uint32_t result = 0;
    socket.recvall(&result, FOUR_BYTES);
    int result_convert = convert_from_uint32_with_endianess(result);
    return result_convert;
}


/*
Pre-Condiciones: Envia mensaje al servidor con el nombre del Usuario. 
Post-Condiciones: -
*/

void ProtocolClient::sendUserName(std::string userName) {
    uint16_t nameSize = convert_to_uint16_with_endianess(userName.size());
    socket.sendall(&nameSize, TWO_BYTES);
    socket.sendall(&userName[0], userName.size());
}

/*
Pre-Condiciones: Envia mensaje al servidor con la operación requerida. 
Post-Condiciones: -
*/

void ProtocolClient::sendOperation(int operationNumber) {
    uint8_t operationNumberConvert = convert_to_uint8(operationNumber);
    socket.sendall(&operationNumberConvert, ONE_BYTE);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la operación crear partida. 
Post-Condiciones: -
*/

void ProtocolClient::sendCreateGameOperation(int operationNumber) {
    this->sendOperation(operationNumber);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la información para crear una
partida.
Post-Condiciones: -
*/

void ProtocolClient::sendCreateGameInfo(std::string gameName,
                                        std::string mapName,
                                        int houseNumber) {
    uint8_t houseNumberConvert = convert_to_uint8(houseNumber);
    uint16_t nameSize = convert_to_uint16_with_endianess(gameName.size());
    uint16_t mapNameSize = convert_to_uint16_with_endianess(mapName.size());
    socket.sendall(&nameSize, TWO_BYTES);
    socket.sendall(&gameName[0], gameName.size());
    socket.sendall(&mapNameSize, TWO_BYTES);
    socket.sendall(&mapName[0], mapName.size());
    socket.sendall(&houseNumberConvert, ONE_BYTE);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la operación unirse.
Post-Condiciones: -
a partida. 
*/

void ProtocolClient::sendJoinGameOperation(int operationNumber,
                                           std::string gameName,
                                           int houseNumber) {
    this->sendOperation(operationNumber);
    uint8_t houseNumberConvert = convert_to_uint8(houseNumber);
    uint16_t gameNameSize = convert_to_uint16_with_endianess(gameName.size());
    socket.sendall(&gameNameSize, TWO_BYTES);
    socket.sendall(&gameName[0], gameName.size());
    socket.sendall(&houseNumberConvert, ONE_BYTE);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la operación de listar.
juegos.
Post-Condiciones: -
*/

void ProtocolClient::sendListGamesOperation(int operationNumber) {
    this->sendOperation(operationNumber);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la operación de listar
mapas. 
Post-Condiciones: -
*/

void ProtocolClient::sendListMapsOperation(int operationNumber) {
    this->sendOperation(operationNumber);
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la lista de
mapas.
Post-Condiciones: -
*/

void ProtocolClient::recvListOfMaps(std::list<std::string>& list) {
    uint16_t numberOfMapsConvert = 0;
    socket.recvall(&numberOfMapsConvert, TWO_BYTES);
    int numberOfMaps = convert_from_uint16_with_endianess(numberOfMapsConvert);
    for (int i = 0; i < numberOfMaps; i ++) {
        uint16_t nameSizeConvert = 0;
        socket.recvall(&nameSizeConvert, TWO_BYTES);
        int nameSize = convert_from_uint16_with_endianess(nameSizeConvert);
        std::string mapName;
        mapName.resize(nameSize);
        socket.recvall(&mapName[0], nameSize);
        list.push_back(mapName);
    }
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la lista de juegos.
Post-Condiciones: -
*/

void ProtocolClient::recvListOfGames(std::list <std::string>& list) {
    uint16_t numberOfGamesConvert = 0;
    socket.recvall(&numberOfGamesConvert, TWO_BYTES);
    int numberOfGames = convert_from_uint16_with_endianess(
                        numberOfGamesConvert);
    for (int i = 0; i < numberOfGames; i++) {
        receiveOneByte();  // number players
        receiveOneByte();  // number players required

        uint16_t nameSizeConvert = 0;
        socket.recvall(&nameSizeConvert, TWO_BYTES);
        int nameSize = convert_from_uint16_with_endianess(nameSizeConvert);
        std::string gameName;
        gameName.resize(nameSize);
        socket.recvall(&gameName[0], nameSize);

        list.push_back(gameName);
    }
}

/*
Pre-Condiciones: Envia mensaje al servidor para pedir construir 
un edificio.
Post-Condiciones: 
*/

void ProtocolClient::sendConstructionPetition(int operation, int type) {
    this->sendOperation(operation);
    uint8_t unitType = convert_to_uint8(type);
    socket.sendall(&unitType, ONE_BYTE);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la información de
ataque.
Post-Condiciones: 
*/

void ProtocolClient::sendAttacknInfo(int operation, int type, int param1,
                                     int param2) {
    this->sendOperation(operation);
    uint8_t unitType = convert_to_uint8(type);
    socket.sendall(&unitType, ONE_BYTE);
    uint16_t parameter1 = convert_to_uint16_with_endianess(param1);
    uint16_t parameter2 = convert_to_uint16_with_endianess(param2);
    socket.sendall(&parameter1, TWO_BYTES);
    socket.sendall(&parameter2, TWO_BYTES);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la información de
movimiento.
Post-Condiciones: 
*/

void ProtocolClient::sendMovementUnit(int operation, int unitId, int x,
                                      int y) {
    this->sendOperation(operation);
    uint16_t id = convert_to_uint16_with_endianess(unitId);
    socket.sendall(&id, TWO_BYTES);
    uint16_t posX = convert_to_uint16_with_endianess(x);
    socket.sendall(&posX, TWO_BYTES);
    uint16_t posY = convert_to_uint16_with_endianess(y);
    socket.sendall(&posY, TWO_BYTES);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la información de
donde posicionar un edificio ya listo (construido).
Post-Condiciones: 
*/

void ProtocolClient::sendBuildingPosition(int operation, int x, int y) {
    this->sendOperation(operation);
    uint16_t posX = convert_to_uint16_with_endianess(x);
    uint16_t posY = convert_to_uint16_with_endianess(y);
    socket.sendall(&posX, TWO_BYTES);
    socket.sendall(&posY, TWO_BYTES);
}

/*
Pre-Condiciones: Envia mensaje al servidor con la información de
persecusión de unidades a otras (de otro jugador). 
Post-Condiciones: 
*/

// void ProtocolClient::sendChasingInfo(int operation, int idChaser,
//                                      int idChased) {
//     this->sendOperation(operation);
//     uint16_t chaser = convert_to_uint16_with_endianess(idChaser);
//     uint16_t chased = convert_to_uint16_with_endianess(idChased);
//     socket.sendall(&chaser, TWO_BYTES);
//     socket.sendall(&chased, TWO_BYTES);
// }

/*
Pre-Condiciones: Envia mensaje al servidor para destruir un edificio propio.
Post-Condiciones: 
*/

void ProtocolClient::sendBuildingDestruction(int operation, int buildingId) {
    this->sendOperation(operation);
    uint16_t id = convert_to_uint16_with_endianess(buildingId);
    socket.sendall(&id, TWO_BYTES);
}

/*
Pre-Condiciones: Recibe mensaje del servidor con el mapa del juego. 
Post-Condiciones: -
*/

void ProtocolClient::recvMap(int& width, int& height,
                             std::vector<std::vector<uint8_t>>& map) {
    int rows = receiveTwoBytes();
    int cols = receiveTwoBytes();
    for (int i = 0; i < rows; i ++) {
        std::vector<uint8_t> row;
        row.resize(cols);
        socket.recvall(&row[0], cols);
        map.push_back(std::move(row));
    }
    height = rows;
    width = cols;
}

/*
Pre-Condiciones: Recibe mensaje del servidor con los centros de
construcción. 
Post-Condiciones: -
*/

std::map<int, int> ProtocolClient::recvConstYards(std::map<int,
                        std::tuple<int, int, int, int, bool>>& constYards,
                        std::string& clientName, int& clientId) {
    std::map<int, int> clientHouses;
    int playersAmount = receiveOneByte();
    std::cout << "players amount " << playersAmount << std::endl;
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
            clientId = i;
            property = true;
        }
        clientHouses[i] = house;
        constYards[i] = std::make_tuple(x * 4, y * 4, i, house, property);
        playerHouses[i] = house;
    }
    return clientHouses;
}

/*
Pre-Condiciones: Recibe mensaje del servidor con las unidades.
Post-Condiciones: -
*/

void ProtocolClient::recvUnits(std::map<int,
                    std::tuple<int, int, int, int, int, bool>>& units,
                               const int& clientId, int& money, int& energy) {
    int playersAmount = receiveTwoBytes();

    for (int i = 0; i < playersAmount; i ++) {
        bool propiety = false;
        int playerId = receiveOneByte();
        int newEnergy = receiveFourBytes();
        int newMoney = receiveFourBytes();

        if (playerId == clientId) {
            energy = newEnergy;
            money = newMoney;
        }

        int unitsAmount = receiveTwoBytes();
        if (clientId == playerId) propiety = true;

        for (int j = 0; j < unitsAmount; j ++) {
            int x = receiveTwoBytes() * 4;
            int y = receiveTwoBytes() * 4;
            int type = receiveOneByte();
            int direction = receiveOneByte();
            int unitId = receiveTwoBytes();
            units[unitId] = std::make_tuple(x, y, type, playerId,
                                            direction, propiety);
        }
    }
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información de los
edificios.
Post-Condiciones: -
*/

std::tuple<int, int, int, int, int, bool> ProtocolClient::recvBuildingInfo(
                                                            int clientId) {
    int playerId = receiveOneByte();
    int buildingId = receiveTwoBytes();
    int buildingType = receiveOneByte();
    int x = receiveTwoBytes();
    int y = receiveTwoBytes();
    bool property = false;
    if (playerId == clientId) property = true;
    return std::make_tuple(x * 4, y * 4, playerId, buildingId, buildingType, property);
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información de un ataque.
Post-Condiciones: -
*/

std::tuple<int, int, int, int> ProtocolClient::receiveAttackInfo() {
    int attackerId = receiveTwoBytes();
    int attackedId = receiveTwoBytes();
    int currentLife = receiveTwoBytes();
    int totalLife = receiveTwoBytes();
    return std::make_tuple(attackerId, attackedId, currentLife, totalLife);
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información del progreso
de las unidades, para cuando se deben entrenar. 
Post-Condiciones: -
*/

void ProtocolClient::recvUnitsProgress(std::vector<std::tuple<int, int>>&
                                       unitsProgress, int clientId) {
    int unitsAmount = receiveTwoBytes();
    for (int i = 0; i < unitsAmount; i ++) {
        int playerId = receiveOneByte();
        int unitType = receiveOneByte();
        int percentage = receiveOneByte();
        if (playerId == clientId) {
            unitsProgress.push_back(std::make_tuple(unitType, percentage));
        }
    }
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información del progreso
de los edificos, para cuando se deben construir. 
Post-Condiciones: -
*/

void ProtocolClient::recvBuildingProgress(std::vector<int>&
                                          buildingsProgress) {
    int buildingType = receiveOneByte();
    int percentage = receiveOneByte();
    buildingsProgress.push_back(buildingType);
    buildingsProgress.push_back(percentage);
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información de empezar
partida.
Post-Condiciones: -
*/

int ProtocolClient::recvStartGame() {
    return receiveOneByte();
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información del resultado
de una operación.
Post-Condiciones: -
*/

int ProtocolClient::recvOperationResult() {
    return receiveOneByte();
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información del numero de
operación. 
Post-Condiciones: -
*/

int ProtocolClient::recvOperationNumber() {
    return receiveOneByte();
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información de un ataque
del gusano de arena. 
Post-Condiciones: -
*/

void ProtocolClient::recvWormAttack(int& x, int& y) {
    x = receiveTwoBytes() * 4;
    y = receiveTwoBytes() * 4;
}

/*
Pre-Condiciones: Recibe mensaje del servidor con la información del estado
de la cosecha y refinamiento de la especia melange.
Post-Condiciones: -
*/

void ProtocolClient::recvRefinementInfo(std::vector<std::tuple<int, int, int>>&
                                        species, std::map<std::tuple<int, int>,
                                        bool> & spice) {
    int tilesAmount = receiveTwoBytes();
    for (int i = 0; i < tilesAmount; i ++) {
        int x = receiveTwoBytes();
        int y = receiveTwoBytes();
        int state = receiveOneByte();
        auto found = spice.find(std::make_tuple(x, y));
        if (found == spice.end()) {
            spice[std::make_tuple(x, y)] = false;
        } else {
            spice[std::make_tuple(x, y)] = true;
        }
        species.push_back(std::make_tuple(x, y, state));
    }
}

/*
Pre-Condiciones: Recibe mensaje del servidor para destruir un edificio
propio. 
Post-Condiciones: -
*/

int ProtocolClient::receiveDestroyedBuilding() {
    return receiveTwoBytes();
}
