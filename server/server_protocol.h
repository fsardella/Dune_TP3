#ifndef __PROTOCOLSERVER_H__
#define __PROTOCOLSERVER_H__

#include "common_socket.h"
#include "common_command.h"
#include <string>
#include "server_gamedata.h"


typedef std::vector<std::vector<int>> sketch_t;

class ProtocolServer {
	Socket socket; //Socket aceptado
	public:
	explicit ProtocolServer(Socket&& socket);
	int convert_from_uint8(uint8_t number);
	int convert_from_uint16_with_endianess(uint16_t number);
	uint16_t convert_to_uint16_with_endianess(int number);
	uint8_t convert_to_uint8(int number);
	int recieve_msg_operation();
	int recieve_msg_house();
	int recieve_msg_required();
	int recieve_msg_bytes();
	std::string recieve_msg_game_name(int bytes);
	void send_msg_result(int response);
	void send_msg_list(GameData game);
	void send_msg_num_list(int size);

    void sendString(const std::string& data);
    void sendCommand(Command command);
    Command recvCommand(int size); // Idea: size en mensajes para que sea automatico
    void send_map_row(std::vector<int>& row); 
    
    void close();
	~ProtocolServer();
};

#endif /*__PROTOCOLSERVER_H__*/
