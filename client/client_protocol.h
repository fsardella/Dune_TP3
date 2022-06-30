#ifndef __PROTOCOLCLIENT_H__
#define __PROTOCOLCLIENT_H__

#include <string>
#include <vector>
#include <list>

#include "common_socket.h"
#include "Construction.h"

#define BUILD_UNIT 5
#define BUILD_CONSTRUCTION 6
#define MOVE_UNIT 7

class ProtocolClient {
    Socket socket;
    std::map<int, int> playerHouses;
    public:
    ProtocolClient();
    void setSktConnection(const char* name_host, const char* service_port);
    int receiveTwoBytes();
    int receiveOneByte();
    int convert_from_uint8(uint8_t number); 
    int convert_from_uint16_with_endianess(uint16_t number);
    uint16_t convert_to_uint16_with_endianess(int number);
    uint8_t convert_to_uint8(int number);

    void sendOperation(int operationNumber);
    void sendUserName(std::string userName);
    void sendCreateGameOperation(int operationNumber);
    void sendCreateGameInfo(std::string gameName, std::string mapName, int houseNumber);
    void sendJoinGameOperation(int operationNumber, std::string gameName, int houseNumber);
    void sendListGamesOperation(int operationNumber);
    void sendListMapsOperation(int operationNumber);
    void sendConstructionPetition(int operation, int type);
    void sendOperationInfo(int operation, int type, int param1, int param2);
    void sendBuildingPosition(int operation, int x, int y);
    void recvListOfMaps(std::list<std::string>& list);
    void recvListOfGames(std::list <std::string>& list);
    std::map<int, int> recvConstYards(std::map<int, std::tuple<int, int, int, int, bool>>& constYards,
									  std::string& clientName, int* clientId);
    void recvMap(int* width, int* height, std::vector<std::vector<uint8_t>>& map);
    void recvUnits(std::map<int, std::tuple<int, int, int, int, int, bool>>& units,
                   int clientId);
    std::tuple<int, int, int, int, int, bool> recvBuildingInfo(int clientId);
    std::tuple<int, int, int, int> receiveAttackInfo();
    void recvUnitsProgress(std::vector<std::tuple<int, int>>& unitsProgress, int clientId);
    void recvBuildingsProgress(std::vector<std::tuple<int, int>>& buildingsProgress);
    int recvStartGame();
    int recvOperationResult();
    int recvOperationNumber();
    ~ProtocolClient();
};

#endif /*__PROTOCOLCLIENT_H__*/
