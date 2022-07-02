#include "yaml_parser.h"
#include <fstream>

#define SAND "sand"
#define DUNE "dune"
#define ROCK "rock"
#define SPICE "spice"
#define MONT "mont"
#define CLIFF "cliff"
#define CONSTRUCTION_YARD "construction yard"

/*
 * Pre-condiciones: Constructor por defecto de la clase YamlParser.
 * Post-condiciones: -
 * */

YamlParser::YamlParser() {}

/*
 * Pre-condiciones: Constructor de la clase YamlParser a partir de
 * un parh a un archivo que contiene la información de un mapa ya creado.
 * Post-condiciones: -
 * */

YamlParser::YamlParser(const std::string& mapPath) : mapPath(mapPath) {}

/*
 * Pre-condiciones: Modifica un archivo con extensión .yaml para incorporar
 * el nombre de un nuevo mapa.
 * Post-condiciones: -
 * */

void YamlParser::addMapName(const std::string& mapName) {
    YAML::Node node;
    try {
        node = YAML::LoadFile(MAPS);

        std::vector<std::string> maps = node["maps"].as<
                                        std::vector<std::string>>();
        maps.push_back(mapName);

        node["maps"] = maps;
    } catch(YAML::BadFile& e) {
        node["maps"].push_back(mapName);
    }
    std::ofstream file(MAPS,  std::ofstream::out);
    file << node;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un vector de strings con el nombre de los
 * mapas creados. Lanza error en caso de que no haya ninguno.
 * */

std::vector<std::string> YamlParser::getMaps() {
    try {
        YAML::Node node = YAML::LoadFile(MAPS);
        std::vector<std::string> maps = node["maps"].as<
                                        std::vector<std::string>>();
        return maps;
    } catch(YAML::BadFile& e) {
        throw(std::length_error("No map has been created"));
    }
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un diccionario de claves y valores strings
 * con los tipos de tiles posibles.
 * */

std::map<std::string, std::string> YamlParser::getItems(
                                const std::string& type) {
    YAML::Node node = YAML::LoadFile(ITEMS);
    std::vector<std::vector<std::string>> listItems = node[type].as<
                            std::vector<std::vector<std::string>>>();
    std::map<std::string, std::string> items;
    for (std::vector<std::string>& item : listItems) {
        items[item[0]] = item[1];
    }
    return items;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un diccionario de claves enteras
 * y valores vector de strings que representa un traductor a partir
 * del cual se puede obtener el nombre y path a una tile utilizando su id.
 * */

std::map<int, std::vector<std::string>> YamlParser::getTranslator() {
    YAML::Node node = YAML::LoadFile(ITEMS);
    std::vector<std::string> types {SAND, DUNE, ROCK, SPICE, MONT,
                                    CLIFF, CONSTRUCTION_YARD};
    std::map<int, std::vector<std::string>> translator;
    int count = 0;
    for (std::string& type : types) {
        std::vector<std::vector<std::string>> listItems = node[type].as<
                                std::vector<std::vector<std::string>>>();
        for (std::vector<std::string>& item : listItems) {
            translator[count] = item;
            count++;
        }
    }
    return translator;
}

/*
 * Pre-condiciones: -
 * Post-condiciones: Devuelve un entero que representa el id de una tile.
 * Lo hace a partir de un tipo de tile y su nombre.
 * */

int YamlParser::getItemId(const std::string& parentType,
                          const std::string& name) {
    YAML::Node node = YAML::LoadFile(ITEMS);
    std::vector<std::vector<std::string>> listItems = node[parentType].as<
                                  std::vector<std::vector<std::string>>>();
    int i;
    for (i = 0; i < static_cast<int>(listItems.size()); i ++) {
        std::string itemName = listItems[i][0];
        if (itemName.compare(name) == 0) {
            break;
        }
    }
    return i;
}

/*
 * Pre-condiciones: Recibe un objeto de la clase Map que contiene toda
 * la información del mapa. En este caso, solo se modifica la matriz del
 * archivo que representa al mapa.
 * Post-condiciones: Edita un archivo con extensión .yaml ya existente.
 * */

void YamlParser::editMap(Map* map) {
    YAML::Node node = YAML::LoadFile(MAPS_ROUTE + mapPath);

    std::string matrix("matrix");
    this->loadMatrix(map->getMap(), node, matrix);

    std::ofstream yaml_file(MAPS_ROUTE + mapPath,  std::ofstream::out);
    yaml_file << node;
}

/*
 * Pre-condiciones: Carga en un archivo .yaml ya existente una nueva
 * matriz que reemplazará a la existente.
 * Post-condiciones: -
 * */

void YamlParser::loadMatrix(std::vector<std::vector<int>> matrix,
                            YAML::Node& node, const std::string& key) {
    YAML::Node new_matrix;
    for (std::vector<int>& row : matrix) {
        YAML::Node yaml_row = YAML::Load("[]");
        for (int& tile : row) {
            yaml_row.push_back(tile);
        }
        new_matrix.push_back(yaml_row);
    }
    node[key] = new_matrix;
}

/*
 * Pre-condiciones: Guarda en una archivo .yaml la información necesaria
 * para describir al mapa editado. Esta información se encuentra en un objeto
 * de la clase Map que se recibe por parámetro. Si la operación es de edición
 * modifica un archivo ya existente, en caso constrario crea un archivo nuevo.
 * Post-condiciones: -
 * */

void YamlParser::saveMap(Map* map) {
    try {  // es edición
        this->editMap(map);
    } catch(YAML::BadFile& e) {  // es creación
        std::ofstream yaml_file(MAPS_ROUTE + mapPath,  std::ofstream::out);
        YAML::Node node = YAML::LoadFile(MAPS_ROUTE + mapPath);

        node["width"] = map->getWidth();
        node["height"] = map->getHeight();
        node["players"] = map->getNPlayers();
        std::string matrix("matrix");
        std::string constructions("constructions");
        this->loadMatrix(map->getMap(), node, matrix);
        this->loadMatrix(map->getConstYards(), node, constructions);

        yaml_file << node;

        std::string mapName = map->getName();
        this->addMapName(mapName);
    }
}

/*
 * Pre-condiciones: Recibe un puntero a un objeto de clase Map y setea
 * en el toda la información necesaria para describir a un mapa ya existente.
 * Esta información la obtiene de un archivo con extensión .yaml.
 * Post-condiciones: -
 * */

void YamlParser::getMap(Map* map) {
    try {
        YAML::Node node = YAML::LoadFile(MAPS_ROUTE + mapPath);

        map->setWidth(node["width"].as<int>());
        map->setHeight(node["height"].as<int>());
        map->setNPlayers(node["players"].as<int>());
        map->setMap(node["matrix"].as<std::vector<std::vector<int>>>());
        map->setConstYards(node["constructions"].as<
                                        std::vector<std::vector<int>>>());
    } catch(YAML::BadFile& e) {
        std::string msg("No map is associated with " + mapPath + "yaml");
        throw(std::ios_base::failure(msg));
    }
}
