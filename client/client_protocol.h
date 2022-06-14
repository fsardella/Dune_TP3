#ifndef __PROTOCOLCLIENT_H__
#define __PROTOCOLCLIENT_H__

#include <string>
#include <vector>

#include "common_socket.h"
#include "Construction.h"

class ProtocolClient {
    Socket socket;
    public:
    ProtocolClient();
    void setSktConnection(const char* name_host, const char* service_port);
    void sendConstructionPetition(Construction construction);
    void send_msg_listar();
    int recieve_msg_count();
    void recieve_msg_listar(uint8_t* current_convert, uint8_t* required_convert,
	std::string* game_name_convert);
    void send_msg_crear(int house, int num_players,
    std::string& game_name);
    int recieve_msg_result();
    void send_msg_unirse(int house, std::string& game_name);
    std::string recieve_msg_game_name(int bytes);
    int convert_from_uint8(uint8_t number); 
    int convert_from_uint16_with_endianess(uint16_t number);
    uint16_t convert_to_uint16_with_endianess(int number);
    uint8_t convert_to_uint8(int number);
    void sendUserName(std::string userName);
    void sendCreateGameOperation(int operationNumber, std::string gameName, std::string mapName, int houseNumber);
    void sendJoinGameOperation(int operationNumber, std::string gameName, int houseNumber);
    void sendListGamesOperation(int operationNumber);
    void sendListMapsOperation(int operationNumber);
    void recvListOfMaps();
    void recvListOfGames();
    void sendOperation(int operationNumber);
    ~ProtocolClient();
};

#endif /*__PROTOCOLCLIENT_H__*/
