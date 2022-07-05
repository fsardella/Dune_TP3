#ifndef __SERVER_UNITDATA_H__
#define __SERVER_UNITDATA_H__

#include <stdint.h>
#include <utility>

typedef std::pair<uint16_t, uint16_t> coor_t;

// Un struct glorificado
class UnitData {
 public:
    coor_t pos;
    uint8_t type;
    uint8_t house;
    uint8_t dir;
    uint16_t id;
    // Constructor vacio e invalido, para la libreria std
    UnitData(): pos(coor_t({0,0})), type(0), house(0), dir(0), id(0xFFFF) {}
    UnitData(coor_t pos, uint8_t house, uint8_t dir, uint16_t id, uint8_t type):
                                        pos(pos), type(type), house(house),
                                        dir(dir), id(id) {}
    ~UnitData() {}
};


#endif
