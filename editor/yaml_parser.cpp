#include "yaml_parser.h"
#include <fstream>

#define SAND "sand"
#define DUNE "dune"
#define ROCK "rock"
#define SPICE "spice"
#define MONT "mont"
#define CLIFF "cliff"
#define CONSTRUCTION_YARD "construction yard"

YamlParser::YamlParser() {}

YamlParser::YamlParser(const std::string& mapPath) : mapPath(mapPath) {}

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

void YamlParser::editMap(Map* map) {
    YAML::Node node = YAML::LoadFile(MAPS_ROUTE + mapPath);

    std::string matrix("matrix");
    this->loadMatrix(map->getMap(), node, matrix);

    std::ofstream yaml_file(MAPS_ROUTE + mapPath,  std::ofstream::out);
    yaml_file << node;
}

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
