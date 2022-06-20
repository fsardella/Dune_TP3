#ifndef __SERVER_UNITDATA_H__
#define __SERVER_UNITDATA_H__

#include <stdint.h>

typedef std::pair<uint16_t, uint16_t> coor_t;

// Un struct glorificado
class UnitData {
    coor_t pos;
    uint8_t type;
    uint8_t house;
    coor_t dir;
 public:
    UnitData();
    UnitData(coor_t pos, uint8_t house);
    coor_t getPos();
    uint8_t getHouse();
    ~UnitData();
};


#endif
