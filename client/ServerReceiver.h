#ifndef __SERVERRECEIVER_H__
#define __SERVERRECEIVER_H__

#include <map>
#include <string>
#include <vector>
#include <tuple>
#include "GameView.h"
#include "../common/thread.h"
#include "client_protocol.h"

class ServerReceiver: public Thread {
    ProtocolClient* protocolClient;
    GameView* gameView;
    std::string& clientName;
    int clientId;
    int& result;
    std::map<int, int> clientHouses;
    std::map<std::tuple<int, int>, bool> spices;
    std::vector<int> unitsUnderConstruction;

 public:
    ServerReceiver(ProtocolClient* protocol, GameView* gameViewObj,
                   std::string& clientName, int& result);
    void receiveBackground();
    void buildConstructionYards();
    void gameLoop();
    void receiveUnits();
    void receiveBuilding();
    void receiveUnitAttack();
    void receiveBuildingAttack();
    bool checkIsStillUnderConstruction(int previousUnit,
                            std::vector<std::tuple<int, int>> unitProgress);
    void receiveUnitProgress();
    void receiveBuildingProgress();
    void receiveWormInfo();
    void receiveRefinementInfo();

    void run() override;
    ~ServerReceiver() override;
};

#endif /*__SERVERRECEIVER_H__*/
