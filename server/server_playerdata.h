#ifndef __SERVER_PLAYER_DATA_H__
#define __SERVER_PLAYER_DATA_H__

#include <string>
#include <stdint.h>

typedef std::pair<uint16_t, uint16_t> coor_t;


// Defino todo en header porque es un struct glorificado esto. Media pila.
class PlayerData {
 public:
    std::string name;
    uint8_t house;
    coor_t base;
    PlayerData(std::string name, uint8_t house, coor_t base): name(name),
                                                              house(house),
                                                              base(base) {}
    ~PlayerData() {}
};

#endif
