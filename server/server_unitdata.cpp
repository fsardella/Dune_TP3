#include "server_unitdata.h"



UnitData::UnitData(): pos(coor_t({0,0})), type(0), house(0), dir(0) {}

UnitData::UnitData(coor_t pos, uint8_t house): pos(pos), type(0),
                                         house(house), dir(0) {} 

coor_t UnitData::getPos() const {
    return this->pos;
}


uint8_t UnitData::getHouse() const {
    return this->house;
}


UnitData::~UnitData() {}
