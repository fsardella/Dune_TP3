#ifndef __PROTOCOLCLIENT_H__
#define __PROTOCOLCLIENT_H__

#include <string>
#include <vector>
#include <list>
#include <map>
#include <tuple>
#include "../common/common_socket.h"
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
    void closeCommunication();
    int receiveOneByte();
    int receiveTwoBytes();
    int receiveFourBytes();
    int convert_from_uint8(uint8_t number);
    int convert_from_uint16_with_endianess(uint16_t number);
    int convert_from_uint32_with_endianess(uint32_t number);
    uint8_t convert_to_uint8(int number);
    uint16_t convert_to_uint16_with_endianess(int number);

    void sendOperation(int operationNumber);
    void sendUserName(std::string userName);
    void sendCreateGameOperation(int operationNumber);
    void sendCreateGameInfo(std::string gameName, std::string mapName,
                            int houseNumber);
    void sendJoinGameOperation(int operationNumber, std::string gameName,
                               int houseNumber);
    void sendListGamesOperation(int operationNumber);
    void sendListMapsOperation(int operationNumber);
    void sendConstructionPetition(int operation, int type);
    void sendAttacknInfo(int operation, int type, int param1, int param2);
    void sendMovementUnit(int operation, int unitId, int x, int y);
    void sendBuildingPosition(int operation, int x, int y);
    // void sendChasingInfo(int operation, int idChaser, int idChased);
    void sendBuildingDestruction(int operation, int buildingId);

    void recvListOfMaps(std::list<std::string>& list);
    void recvListOfGames(std::list <std::string>& list);
    std::map<int, int> recvConstYards(std::map<int,
                            std::tuple<int, int, int, int, bool>>& constYards,
                            std::string& clientName, int& clientId);
    void recvMap(int& width, int& height,
                 std::vector<std::vector<uint8_t>>& map);
    void recvUnits(std::map<int,
                  std::tuple<int, int, int, int, int, bool>>& units,
                  const int& clientId, int& money, int& energy);
    std::tuple<int, int, int, int, int, bool> recvBuildingInfo(int clientId);
    std::tuple<int, int, int, int, int> receiveAttackInfo();
    void recvUnitsProgress(std::vector<std::tuple<int, int>>& unitsProgress,
                           int clientId);
    void recvBuildingProgress(std::vector<int>& buildingsProgress);
    int recvStartGame();
    int recvOperationResult();
    int recvOperationNumber();
    void recvWormAttack(int& x, int& y);
    void recvRefinementInfo(std::vector<std::tuple<int, int, int>>& species,
                            std::map<std::tuple<int, int>, bool> & spice);
    int receiveDestroyedBuilding();

    ~ProtocolClient();
};

#endif /*__PROTOCOLCLIENT_H__*/
