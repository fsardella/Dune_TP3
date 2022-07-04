#include "server_unitbuffer.h"



#define TRIKE 0


UnitBuffer::UnitBuffer(uint8_t type, std::string playerName, TerrainMap& terr,
                       uint8_t playerID, Config* c, std::list<Command>& events):
                                          c(c),
                                          type(type),
                                          playerName(playerName),
                                          playerID(playerID),
                                          terr(terr),
                                          events(events) {
    switch (type) {
        case TRIKE:
            this->count = c->TRIKE_CTIME;
            break;
        case HARVESTER:
            this->count = c->HARVESTER_CTIME;
            break;
        default:
            this->count = 1000;
            break;
    }
    this->totalCount = this->count;
}


bool UnitBuffer::willItEnd(uint16_t seconds) {
    if (seconds == 0)
        return false;
    return seconds >= this->count;
}

void UnitBuffer::process(uint16_t seconds) {
    if (seconds >= this->count) {
        this->count = 0;
        return;
    }
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
            return new Trike(coor, this->terr, newID, this->playerName, c);
        case HARVESTER:
            return new Harvester(coor, this->terr, newID, this->playerName, c);
        default:
            return nullptr;
    }
}

UnitBuffer::~UnitBuffer() {}
