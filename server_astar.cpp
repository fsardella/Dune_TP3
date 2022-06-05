#include "server_units.h"

#include <queue>
#include <math.h>

#include <iostream>

#define WALL 0
#define CHUNKSIZE 4


coor_t getChunk(const coor_t& coor) {
    return coor_t(coor.first - coor.first % CHUNKSIZE, 
                  coor.second - coor.second % CHUNKSIZE);
}


AStar::AStar(Unit& unit, coor_t origin, TerrainMap& terrain): unit(unit),
                                                    terr(terrain),
                                                    actPos(origin),
                                                    actDest(coor_t(0, 0)) {}

bool AStar::pathIsClear() {
    for (coor_t mov : this->movs) {
        if (this->terr.getSpeed(mov, this->unit) == WALL)
            return false;
    }
    return true;
}

void AStar::processMove(coor_t dest) {
    if (this->actPos == dest || this->terr.getSpeed(dest, this->unit) == WALL) {
        return;
    } else if (!this->movs.empty() && this->actDest == dest
               && (this->pathIsClear() || this->movs.back() == this->actPos)) {
        coor_t ret = this->movs.back();
        this->movs.pop_back();
        this->terr.swapContent(this->actPos, ret);
        this->actPos = ret;
    } else if (this->movs.empty() && !this->chunks.empty()) { 
        this->execSubAlgorithm();
        if (!this->movs.empty())
            this->processMove(this->actDest);
    } else {
        this->movs.clear();
        this->chunks.clear();
        this->actDest = dest;
        this->execAlgorithm();
        if (!this->chunks.empty())
            this->processMove(this->actDest);
    }
}



float AStar::chevychev(const coor_t& coord) {
    float dist_x = abs(coord.first - this->actDest.first);
    float dist_y = abs(coord.second - this->actDest.second);
    return (dist_x > dist_y)? dist_x : dist_y;
}

float get_distance(std::map<coor_t, float>& dict, const coor_t& key) {
    if (dict.find(key) == dict.end()) {
        return INFINITY;
    }
    return dict[key];
}

std::list<coor_t> AStar::getAdjacents(const coor_t& coor) {
    std::list<coor_t> adjacents;
    coor_t dims = this->terr.getDims();
    for (int i = -CHUNKSIZE; i <= CHUNKSIZE; i++) {
        for (int j = -CHUNKSIZE; j <= CHUNKSIZE; j++) {
            if (coor.first + i < (int)dims.first && coor.first + i >= 0 &&
                coor.second + j < (int)dims.second
                && coor.second + j >= 0) {
                coor_t new_coor(coor.first + i, coor.second + j);
                adjacents.push_back(new_coor);
            }
        }
    }
    return adjacents;
}

typedef std::pair<coor_t, float> dijk_t;


bool get_min(const dijk_t& a, const dijk_t& b) {
    return (a.second > b.second);
}

std::map<coor_t, coor_t> AStar::_execAlgorithm() {
    std::map<coor_t, float> distance;
    std::map<coor_t, coor_t> parent;
    std::priority_queue<dijk_t, std::vector<dijk_t>, decltype(&get_min)>
        prior_q(get_min); // Debe ser float para admitir inf...
    coor_t actChunk = getChunk(this->actPos);
    coor_t destChunk = getChunk(this->actDest);
    distance[actChunk] = 0;
    parent[destChunk] = destChunk;
    dijk_t act(actChunk, 0);
    prior_q.push(act);
    while (!prior_q.empty()) {
        coor_t u = prior_q.top().first;
        if (u == destChunk)
            break;
        prior_q.pop();
        for (coor_t adj : getAdjacents(u)) {
            if (distance.find(adj) == distance.end()) {
                float ter_speed = this->terr.getSpeed(adj, this->unit); 
                if (ter_speed == WALL) {
                    distance[adj] = INFINITY;
                } else if (get_distance(distance, adj) >
                           distance[u] + ter_speed + chevychev(adj)) {
                    distance[adj] = distance[u] + ter_speed + chevychev(adj);
                    parent[adj] = u;
                    act = dijk_t(adj, distance[adj]);
                    prior_q.push(act);
                }
            }
        }
    }
    return parent;
}


void AStar::execAlgorithm() {
    std::map<coor_t, coor_t> parents = this->_execAlgorithm();
    coor_t actChunk = getChunk(this->actPos);
    coor_t destChunk = getChunk(this->actDest);
    coor_t u = destChunk;
    while (u != actChunk) {
        //for (float trav_turns = 0;
             //trav_turns < this->terr.getSpeed(u, this->unit);
             //trav_turns++)
        this->chunks.push_back(u);
        u = parents[u];
        if (u == destChunk) {
            this->chunks.clear();
            return;
        }
    }
}

std::list<coor_t> AStar::getSubAdjacents(const coor_t& coor) {
    std::list<coor_t> adjacents;
    coor_t dims = this->terr.getDims();
    dims = coor_t(dims.first, dims.second);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (coor.first + i < (int)dims.first && coor.first + i >= 0 &&
                coor.second + j < (int)dims.second
                && coor.second + j >= 0) {
                coor_t new_coor(coor.first + i, coor.second + j);
                adjacents.push_back(new_coor);
            }
        }
    }
    return adjacents;
}


std::map<coor_t, coor_t> AStar::_execSubAlgorithm(const coor_t& dest) {
    std::map<coor_t, float> distance;
    std::map<coor_t, coor_t> parent;
    std::priority_queue<dijk_t, std::vector<dijk_t>, decltype(&get_min)>
        prior_q(get_min); // Debe ser float para admitir inf...
    distance[this->actPos] = 0;
    parent[dest] = dest;
    dijk_t act(this->actPos, 0);
    prior_q.push(act);
    while (!prior_q.empty()) {
        coor_t u = prior_q.top().first;
        if (u == dest)
            break;
        prior_q.pop();
        for (coor_t adj : getSubAdjacents(u)) {
            if (distance.find(adj) == distance.end()) {
                float ter_speed = this->terr.getSpeed(getChunk(adj), this->unit); 
                if (ter_speed == WALL) {
                    distance[adj] = INFINITY;
                } else if (get_distance(distance, adj) >
                           distance[u] + ter_speed + chevychev(adj)) {
                    distance[adj] = distance[u] + ter_speed + chevychev(adj);
                    parent[adj] = u;
                    act = dijk_t(adj, distance[adj]);
                    prior_q.push(act);
                }
            }
        }
    }
    return parent;
}

void AStar::execSubAlgorithm() {
    coor_t dest = this->chunks.back();
    this->chunks.pop_back();
    std::map<coor_t, coor_t> parents = this->_execSubAlgorithm(dest);
    coor_t u = dest;
    while (u != this->actPos) {
        for (float trav_turns = 0;
             trav_turns < this->terr.getSpeed(getChunk(u), this->unit);
             trav_turns++)
            this->movs.push_back(u);
        u = parents[u];
        if (u == dest) {
            this->movs.clear();
            return;
        }
    }
}

coor_t AStar::getPosition() {
    return this->actPos;
}
