#include "server_units.h"

#include <queue>
#include <math.h>

#include <iostream>

#define WALL 0
#define CHUNKSIZE 8

#define IDLE 4 // direccion

coor_t getChunk(const coor_t& coor) {
    return coor_t((coor.first / CHUNKSIZE) * CHUNKSIZE, 
                  (coor.second / CHUNKSIZE) * CHUNKSIZE);
}


AStar::AStar(Unit& unit, coor_t origin, TerrainMap& terrain): unit(unit),
                                                    terr(terrain),
                                                    actPos(origin),
                                                    actDest(coor_t(0, 0)),
                                                    dir(IDLE) {}


uint8_t AStar::getDir() {
    return this->dir;
}

void AStar::eraseUnitFromMap() {
    this->terr.eraseUnitFromMap(this->actPos);
}

void AStar::setDir(coor_t ant, coor_t actual) {
    int x = (int)actual.second - (int)ant.second + 1;
    int y = (int)actual.first - (int)ant.first + 1;
    this->dir = (uint16_t) x + 3 * y;
    
}

float AStar::getSpeedMod() {
    return this->terr.getSpeedMod(this->actPos);
}

// La solucion de agregar un booleano para saber cuando se esta atacando a un
// edificio me parece personalmente horripilante... Pero no hay tiempo. Too bad!
// https://youtu.be/k238XpMMn38

bool AStar::processMove(coor_t dest, bool attackingBuilding) {
    std::cout << "EMPIEZA\n";
    if (this->actPos == dest || (this->terr.isBlocked(dest) && !attackingBuilding)) {
        this->dir = IDLE;
        std::cout << "llego a destino\n";
        return true;
    } else if (!this->movs.empty() && this->actDest == dest) {
        coor_t ret = this->movs.back();
        if (this->terr.isOccupied(ret)) {
            this->dir = IDLE; // Esperar hasta que la posicion siguiente
            std::cout << "posicion siguiente ocupada\n";
            return true;           // este desocupada
        } else if (this->terr.isBlocked(ret)) {
            this->movs.clear();   // Si justo en frente construyeron,
            this->chunks.clear(); // volver a calcular todo de vuelta
            std::cout << "me bloquearon el camino\n";
            return this->processMove(this->actDest);
        }
        this->movs.pop_back();
        this->terr.swapContent(this->actPos, ret);
        this->setDir(this->actPos, ret);
        this->actPos = ret;
        std::cout << "me muevo\n";
        return true;
    } else if (this->movs.empty() && !this->chunks.empty()) { 
        this->execSubAlgorithm();
        std::cout << "se ejecuta el subalgoritmo\n";
        if (!this->movs.empty()) {
            std::cout << "los movimeintos no estaban vacios\n";
            if (dest != this->chunks.front())
                this->chunks.push_front(dest);
            std::cout << "llego bien\n";
            return this->processMove(this->actDest);
        }
    } else {
        this->movs.clear();
        this->chunks.clear();
        this->actDest = dest;
        this->execAlgorithm();
        std::cout << "se ejecuta el algoritmo\n";
        if (!this->chunks.empty())
            return this->processMove(this->actDest);
    }
    std::cout << "devuelvo false\n";
    return false;
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
    for (int i = -CHUNKSIZE; i <= CHUNKSIZE; i += CHUNKSIZE) {
        for (int j = -CHUNKSIZE; j <= CHUNKSIZE; j += CHUNKSIZE) {
            if (i == 0 && j == 0)
                continue;
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
    std::map<coor_t, bool> seen;
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
        seen[u] = true;
        for (coor_t adj : getAdjacents(u)) {
            if (seen.find(adj) == seen.end()) {
                float ter_speed = this->terr.getSpeedWeight(adj, this->unit); 
                if (ter_speed == WALL) {
                    distance[adj] = INFINITY;
                } else if (get_distance(distance, adj) >
                           distance[u] + ter_speed + chevychev(adj)) {
                    distance[adj] = distance[u] + ter_speed;
                    parent[adj] = u;
                    act = dijk_t(adj, distance[adj] + chevychev(adj));
                    prior_q.push(act);
                }
            }
        }
    }
    return parent;
}

coor_t AStar::addOffset(coor_t chunk) {
    return coor_t(chunk.first + this->actPos.first % CHUNKSIZE,
                  chunk.second + this->actPos.second % CHUNKSIZE);
}

void AStar::execAlgorithm() {
    std::map<coor_t, coor_t> parents = this->_execAlgorithm();
    coor_t actChunk = getChunk(this->actPos);
    coor_t destChunk = getChunk(this->actDest);
    coor_t u = destChunk;
    while (u != actChunk) {
        this->chunks.push_back(addOffset(u));
        u = parents[u];
        if (u == destChunk) {
            this->chunks.clear();
            return;
        }
    }
    this->chunks.pop_back();
    this->chunks.push_back(this->actDest);
}


std::list<coor_t> AStar::getSubAdjacents(const coor_t& coor) {
    std::list<coor_t> adjacents;
    coor_t dims = this->terr.getDims();
    dims = coor_t(dims.first, dims.second);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
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


float subChevychev(const coor_t& coord, const coor_t& dest) {
    float dist_x = abs(coord.first - dest.first); // posible bug por no castear???
    float dist_y = abs(coord.second - dest.second);
    return (dist_x > dist_y)? dist_x : dist_y;
}

std::map<coor_t, coor_t> AStar::_execSubAlgorithm(const coor_t& dest) {
    std::map<coor_t, float> distance;
    std::map<coor_t, bool> seen;
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
        seen[u] = true;
        for (coor_t adj : getSubAdjacents(u)) {
            if (seen.find(adj) == seen.end()) {
                float ter_speed = this->terr.getSpeedWeight(adj, this->unit); 
                if (ter_speed == WALL) {
                    distance[adj] = INFINITY;
                } else if (get_distance(distance, adj) >
                           distance[u] + ter_speed + subChevychev(adj, dest)) {
                    distance[adj] = distance[u] + ter_speed + subChevychev(adj, dest);
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
            this->movs.push_back(u);
        u = parents[u];
        if (u == dest) {
            this->movs.clear();
            return;
        }
    }
}


void AStar::print() {
    std::cout << "A* Chunks: ";
    for (coor_t chunk : this->chunks)
        std::cout << chunk.first << ", " << chunk.second << " -> ";
    std::cout << std::endl;
    std::cout << "A* Moves: ";
    for (coor_t mov : this->movs)
        std::cout << mov.first << ", " << mov.second << " -> ";
    std::cout << std::endl;
}

coor_t AStar::getPosition() {
    return this->actPos;
}
