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
	void operation_run(std::string& line);
	void print_crear_result(int result);
	void print_unirse_result(int result);
	void print_listar_result();
	int get_number_house(std::string& house);
	ProtocolClient protocol;
	public:
	Client(const char* name_host, const char* service_port);
	int client_run();
	~Client();
};

#endif /*__CLIENTE_H__*/
