#include "server_worm.h"


#define MAX_TRIES 300
#define CHUNKSIZE 8

Worm::Worm(TerrainMap& terr, uint32_t delay): terr(terr), delay(delay) {}

void Worm::surface(std::list<Command>& events) {
    coor_t dims = this->terr.getDims();
    for (int tries = 0; tries < MAX_TRIES; tries++) {
        coor_t coor(rand() % dims.first, rand() % dims.second);
        if (this->terr.isSand(coor)) {
            Command comm;
            comm.add8BytesMessage(WORM);
            comm.setType(WORM);
            comm.add16BytesMessage(coor.second);
            comm.add16BytesMessage(coor.first);
            events.push_back(comm);
            this->eatPeople(events, coor);
            break;
        }
    }
}

void Worm::eatPeople(std::list<Command>& events, coor_t coor) {
    for (int i = -CHUNKSIZE; i <= CHUNKSIZE; i += CHUNKSIZE) {
        for (int j = -CHUNKSIZE; j <= CHUNKSIZE; j += CHUNKSIZE) {
            coor_t actCoor(coor.first + i, coor.second + j);
            if (!this->terr.isSand(actCoor))
                continue;
            std::list<Unit*> deads = this->terr.getAllUnits(actCoor);
            for (Unit* dead : deads)
                dead->kill(events);
        }
    }
}


void Worm::update(std::list<Command>& events) {
    this->actTime += 1;
    if (this->actTime >= this->delay) {
        this->surface(events);
        this->actTime = 0;
    }
}

Worm::~Worm() {}
