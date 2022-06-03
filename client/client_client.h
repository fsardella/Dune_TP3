#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <string>
#include <vector>
#include "client_protocol.h"

class Client {
	std::string operation;
	std::string house;
	std::string num_players;
	std::string game_name;
	std::string game_name_len;
	ProtocolClient protocol;
	int get_number_house(std::string& house);
	void operation_run(std::string& line);
	public:
	Client(const char* name_host, const char* service_port);
	int client_run();
	~Client();
};

#endif /*__CLIENTE_H__*/
