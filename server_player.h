#ifndef __SERVER_PLAYER_H
#define __SERVER_PLAYER_H

#include <stdint.h>
#include <list>
#include "server_units.h"

class Player {
    std::string playerName;
    int house;
    std::list<Unit*> units;
    //  TODO BUILDINGS
 public:
    Player(const int& house, const std::string& playerName);
    ~Player();
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(Player&&);
    Player& operator=(Player&&);
};

#endif
