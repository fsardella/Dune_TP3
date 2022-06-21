#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <string>
#include <vector>
#include "client_protocol.h"
#include <yaml-cpp/yaml.h>
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "SdlWindow.h"
#include "GameView.h"
#include "ServerReceiver.h"
#include <QDialog>

#define HOUSE_ATREIDES "Atreides"
#define HOUSE_HARKONNEN "Harkonnen"
#define HOUSE_ORDOS "Ordos"
#define OPERACION_LISTAR "listar"
#define OPERACION_CREAR "crear"
#define OPERACION_UNIRSE "unirse"
#define OPERACION_FIN "fin"

#define JOIN_GAME 1
#define LIST_GAMES 2
#define CREATE_GAME 3
// #define LIST_MAPS 4


class Client {
	int houseNumber;
	std::string gameName;
	std::string mapName;
	void operation_run(std::string& line);
	public:
	ProtocolClient protocol; //get protocol despues
	Client();
	void setConnection(const char* name_host, const char* service_port);
	void client_run();
	void chooseNumberHouse(std::string house);
	void chooseGameName(std::string name);
	void chooseMapName(std::string name);
	void sendUserName(std::string userName);
	void sendCreateGameOperation();
	void sendCreateGameInfo();
	void sendJoinGameOperation();
	void sendListGamesOperation();
	void sendListMapsOperation();
	void recvListOfMaps(std::list <std::string>& list);
    void recvListOfGames(std::list <std::string>& list);
	int recvStartGame();
	int recvOperationResult();
	~Client();
};

#endif /*__CLIENTE_H__*/
