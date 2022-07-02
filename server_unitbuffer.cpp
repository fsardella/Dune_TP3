#include "server_unitbuffer.h"



#define TRIKE 0


UnitBuffer::UnitBuffer(uint8_t type, std::string playerName, TerrainMap& terr,
                       uint8_t playerID): type(type),
                                          playerName(playerName),
                                          playerID(playerID),
                                          terr(terr) {
    switch (type) {
        case TRIKE:
            this->count = 6000; // 2m * 60 = 120, * 10 = 1200, * 5 = 6000
        case HARVESTER:
            this->count = 9000;
        default:
            this->count = 69;
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

uint8_t UnitBuffer::getTimeToEnd() {
    uint8_t ret = 100 - (uint8_t)(100 * (float)this->count / (float)this->totalCount);
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
