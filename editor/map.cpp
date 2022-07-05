#include "map.h"
#include <utility>

/*
 * Pre-condiciones: Constructor de la clase Map.
 * Post-condiciones: -
 * */

Map::Map() {}

/*
 * Pre-condiciones: Recibe un nombre de mapa.
 * Post-condiciones: Setea en uno de sus atributos el nombre del
 * mapa seleccionado.
 * */

void Map::setName(const std::string& mapName) {
    this->name = mapName;
}

/*
 * Pre-condiciones: Recibe el ancho del mapa.
 * Post-condiciones: Setea en uno de sus atributos el ancho del
 * mapa seleccionado.
 * */

void Map::setWidth(int mapWidth) {
    this->width = mapWidth;
}

/*
 * Pre-condiciones: Recibe el largo del mapa.
 * Post-condiciones: Setea en uno de sus atributos el largo del
 * mapa seleccionado.
 * */

void Map::setHeight(int mapHeight) {
    this->height = mapHeight;
}

/*
 * Pre-condiciones: Recibe la cantidad de jugadores requeridos.
 * Post-condiciones: Setea en uno de sus atributos la cantidad
 * de jugadores requeridos seleccionada.
 * */

void Map::setNPlayers(int mapNPlayers) {
    this->nPlayers = mapNPlayers;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Setea que el mapa a editar no es nuevo.
 * */

void Map::setIsNotNew() {
    this->isNew = false;
}

/*
 * Pre-condiciones: Recibe una matriz de enteros (vector de vectores).
 * Post-condiciones: Setea en uno de sus atributos la matriz que
 * representa al mapa.
 * */

void Map::setMap(std::vector<std::vector<int>> map) {
    this->map = map;
}

/*
 * Pre-condiciones: Recibe un vector de vectores de enteros con
 * las posiciones de los centros de construcción.
 * Post-condiciones: Setea en uno de sus atributos las coodenadas de
 * los centros de construcción.
 * */

void Map::setConstYards(std::vector<std::vector<int>> constYards) {
    this->constYards = constYards;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el nombre del mapa.
 * */

std::string Map::getName() {
    return this->name;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el ancho del mapa.
 * */

int Map::getWidth() {
    return this->width;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve el largo del mapa.
 * */

int Map::getHeight() {
    return this->height;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve la cantidad de jugadores requeridos.
 * */

int Map::getNPlayers() {
    return this->nPlayers;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un booleano que representa si
 * el mapa era nuevo (true) o era uno ya existente (false).
 * */

bool Map::getIsNew() {
    return this->isNew;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un vector de vectores de enteros
 * que representa al mapa.
 * */

std::vector<std::vector<int>> Map::getMap() {
    return this->map;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un vector de vectores de enteros
 * que representa las posiciones de los centros de construcción.
 * */

std::vector<std::vector<int>> Map::getConstYards() {
    return this->constYards;
}

/*
 * Pre-condiciones: Modifica el mapa en la posición formada por
 * (col, row) e inserta en la misma el id recibido.
 * Post-condiciones: -
 * */

void Map::modifyMapAt(int row, int column, int id) {
    map[row][column] = id;
}

/*
 * Pre-condiciones: Agrega un nuevo centro de construcción a partir
 * de su posición.
 * Post-condiciones: -
 * */

void Map::addConst(int row, int column) {
    std::vector<int> position = {row, column};
    constYards.push_back(position);
}

/*
 * Pre-condiciones: Elimina un centro de construcción a partir
 * de su posición.
 * Post-condiciones: -
 * */

void Map::deleteConst(int row, int column) {
    int deleteIndex = 0;
    for (size_t i = 0; i < constYards.size(); i ++) {
        if (constYards.at(i).at(0) == row &&
            constYards.at(i).at(1) == column) {
            deleteIndex = i;
        }
    }
    constYards.erase(constYards.begin() + deleteIndex);
}

/*
 * Pre-condiciones: Constructor por movimiento de la clase Map.
 * Post-condiciones: -
 * */

Map::Map(Map &&other) {
    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->nPlayers = other.nPlayers;
    this->map = std::move(other.map);
    this->constYards = other.constYards;

    other.width = 0;
    other.height = 0;
    other.nPlayers = 0;
}

/*
 * Pre-condiciones: Constructor por movimiento de la clase Map con
 * operador =.
 * Post-condiciones: -
 * */

Map &Map::operator=(Map &&other)  {
    if (this == &other) {
        return *this;
    }

    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->nPlayers = other.nPlayers;
    this->map = std::move(other.map);
    this->constYards = other.constYards;

    other.width = 0;
    other.height = 0;
    other.nPlayers = 0;

    return *this;
}
