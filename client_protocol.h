#ifndef __PROTOCOLCLIENT_H__
#define __PROTOCOLCLIENT_H__

#include <string>
#include <vector>

#include "common_socket.h"

class ProtocolClient {
    Socket socket;
    public:
    ProtocolClient(const char* name_host, const char* service_port);
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
    void sendMsgNombre(const std::string& playerName);
    ~ProtocolClient();
};

#endif /*__PROTOCOLCLIENT_H__*/
