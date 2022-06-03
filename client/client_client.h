#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <string>
#include <vector>
#include "client_protocol.h"


#define HOUSE_ATREIDES "Atreides"
#define HOUSE_HARKONNEN "Harkonnen"
#define HOUSE_ORDOS "Ordos"
#define OPERACION_LISTAR "listar"
#define OPERACION_CREAR "crear"
#define OPERACION_UNIRSE "unirse"
#define OPERACION_FIN "fin"


class Client {
	std::string operation;
	std::string house;
	std::string num_players;
	std::string game_name_len;
	ProtocolClient protocol;
	int houseNumber;
	std::string game_name;
	std::string map_name;
	void operation_run(std::string& line);
	public:
	//Client(const char* name_host, const char* service_port);
	Client();
	void setProtocol(const char* name_host, const char* service_port);
	int client_run();
	void chooseNumberHouse(std::string house);
	void chooseGameName(std::string name);
	void chooseMapName(std::string name);
	~Client();
};

#endif /*__CLIENTE_H__*/
