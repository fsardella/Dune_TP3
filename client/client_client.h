#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include <yaml-cpp/yaml.h>
#include <QDialog>
#include <string>
#include <vector>
#include <list>
#include "client_protocol.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "SdlWindow.h"
#include "GameView.h"
#include "ServerReceiver.h"

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
    bool readyToRun;
    int houseNumber;
    std::string gameName;
    std::string mapName;
    std::string name;
    int gameResult;
    void operation_run(std::string& line);

 public:
    ProtocolClient protocol;  // get protocol despues
    Client();
    void setReadyToRun();
    bool isReadyToRun();
    int getGameResult();
    void setConnection(const char* name_host, const char* service_port);
    void closeCommunication();
    void closeGame();
    void client_run();
    void chooseName(std::string name);
    void chooseNumberHouse(std::string house);
    void chooseGameName(std::string name);
    void chooseMapName(std::string name);
    void sendUserName();
    void sendCreateGameOperation();
    void sendCreateGameInfo();
    void sendJoinGameOperation();
    void sendListGamesOperation();
    // void sendListMapsOperation();
    void recvListOfMaps(std::list <std::string>& list);
    void recvListOfGames(std::list <std::string>& list);
    int recvStartGame();
    int recvOperationResult();
    ~Client();
};

#endif /*__CLIENTE_H__*/
