#include "yaml_parser.h"
#include <fstream>

YamlParser::YamlParser() {}

YamlParser::YamlParser(std::string& mapPath) : mapPath(mapPath) {}

void YamlParser::addMapName(std::string& mapName) {
    YAML::Node node;
    try {
        node = YAML::LoadFile(MAPS);

        std::vector<std::string> maps = node["maps"].as<std::vector<std::string>>();
        maps.push_back(mapName);

        node["maps"] = maps; // lo modificas
    } catch(YAML::BadFile& e) {
        node["maps"].push_back(mapName);
    }
    std::ofstream file(MAPS,  std::ofstream::out); // lo creo
    file << node; // lo cargas
}

std::vector<std::string> YamlParser::getMaps() {
    try {
        YAML::Node node = YAML::LoadFile(MAPS);
        std::vector<std::string> maps = node["maps"].as<std::vector<std::string>>();
        return maps;
    } catch(YAML::BadFile& e) {
        throw(std::length_error("No map has been created"));
    }
}

void YamlParser::loadMatrix(std::vector<std::vector<int>> matrix, YAML::Node& node) {
    YAML::Node new_matrix;
    for (std::vector<int>& row : matrix) {
        YAML::Node yaml_row = YAML::Load("[]");
        for (int& tile : row) {
            yaml_row.push_back(tile);
        }
        new_matrix.push_back(yaml_row);
    }
    node["matrix"] = new_matrix;
}

void YamlParser::editMap(Map* map) {
    YAML::Node node = YAML::LoadFile(mapPath);

    this->loadMatrix(map->getMap(), node);

    std::ofstream yaml_file(mapPath,  std::ofstream::out);
    yaml_file << node;
}

void YamlParser::saveMap(Map* map) {
    try { // es edición
        this->editMap(map);
    } catch(YAML::BadFile& e) { // es creación
        std::ofstream yaml_file(mapPath,  std::ofstream::out);
        YAML::Node node = YAML::LoadFile(mapPath);

        node["width"] = map->getWidth();
        node["height"] = map->getHeight();
        node["players"] = map->getNPlayers();
        this->loadMatrix(map->getMap(), node);

        yaml_file << node;
    }
}

void YamlParser::getMap(Map* map) {
    YAML::Node node = YAML::LoadFile(mapPath);

    map->setWidth(node["width"].as<int>());
    map->setHeight(node["height"].as<int>());
    map->setNPlayers(node["players"].as<int>());
    map->setMap(node["matrix"].as<std::vector<std::vector<int>>>());
}