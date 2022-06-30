#include "server_unitbuffer.h"



#define TRIKE 0


UnitBuffer::UnitBuffer(uint8_t type, std::string playerName, TerrainMap& terr,
                       uint8_t playerID): type(type),
                                          playerName(playerName),
                                          playerID(playerID),
                                          terr(terr) {
    switch (type) {
        case TRIKE:
            this->count = 1200; // 2m * 60 = 120, * 10 = 1200
    }
    this->totalCount = this->count;
}


bool UnitBuffer::willItEnd(uint16_t seconds) {
    if (seconds == 0)
        return false;
    return seconds >= this->count;
}

void UnitBuffer::process(uint16_t seconds) {
    this->count -= seconds;
    if (seconds == 0)
        this->count = this->totalCount;
}

std::string UnitBuffer::getPlayerName() {
    return this->playerName;
}

uint8_t UnitBuffer::getPlayerID() {
    return this->playerID;
}

uint8_t UnitBuffer::getType() {
    return this->type;
}

uint16_t UnitBuffer::getTimeToEnd() {
    uint16_t ret = 100 - (uint16_t)(100 * (float)this->count / (float)this->totalCount);
    return (ret == 0)? 1 : ret;
}


Unit* UnitBuffer::getResult(coor_t coor, uint16_t newID) {
    switch (this->type) {
        case TRIKE:
            return new Vehicle(coor, this->terr, newID, this->playerName);
        default:
            return nullptr;
    }
}

UnitBuffer::~UnitBuffer() {}
