#ifndef __SERVERRECEIVER_H__
#define __SERVERRECEIVER_H__

#include <map>
#include <string>
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
    void receiveUnitProgress();
    void receiveBuildingProgress();
    void receiveWormInfo();
    void receiveRefinementInfo();

    void run() override;
    ~ServerReceiver() override;
};

#endif /*__SERVERRECEIVER_H__*/
