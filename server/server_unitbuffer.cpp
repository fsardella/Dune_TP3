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
        case RAIDER:
            this->count = c->RAIDER_CTIME;
            break;
        case TANK:
            this->count = c->TANK_CTIME;
            break;
        case HARVESTER:
            this->count = c->HARVESTER_CTIME;
            break;
        case DEVIATOR:
            this->count = c->DEVIATOR_CTIME;
            break;
        case DEVASTATOR:
            this->count = c->DEVASTATOR_CTIME;
            break;
        case SONIC_TANK:
            this->count = c->SONIC_TANK_CTIME;
            break;
        case LIGHT_INFANTRY:
            this->count = c->LIGHT_INFANTRY_CTIME;
            break;
        case HEAVY_INFANTRY:
            this->count = c->HEAVY_INFANTRY_CTIME;
            break;
        case FREMEN:
            this->count = c->FREMEN_CTIME;
            break;
        case SARDAUKAR:
            this->count = c->SARDAUKAR_CTIME;
            break;
        default:
            this->count = 0;
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
        case RAIDER:
            return new Raider(coor, this->terr, newID, this->playerName, c);
        case TANK:
            return new Tank(coor, this->terr, newID, this->playerName, c);
        case HARVESTER:
            return new Harvester(coor, this->terr, newID, this->playerName, c);
        case DEVIATOR:
            return new Deviator(coor, this->terr, newID, this->playerName, c);
        case DEVASTATOR:
            return new Devastator(coor, this->terr, newID, this->playerName, c, 
                                  this->events);
        case SONIC_TANK:
            return new SonicTank(coor, this->terr, newID, this->playerName, c,
                                 this->events);
        case LIGHT_INFANTRY:
            return new LightInfantry(coor, this->terr, newID, this->playerName, c);
        case HEAVY_INFANTRY:
            return new HeavyInfantry(coor, this->terr, newID, this->playerName, c);
        case FREMEN:
            return new Fremen(coor, this->terr, newID, this->playerName, c);
        case SARDAUKAR:
            return new Sardaukar(coor, this->terr, newID, this->playerName, c);
        default:
            return nullptr;
    }
}

UnitBuffer::~UnitBuffer() {}
