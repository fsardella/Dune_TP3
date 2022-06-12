#ifndef YAML_PASER_H
#define YAML_PARSER_H

#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include "map.h"

#define MAPS "maps.yaml"
// #define MAPS_ROUTE ""

class YamlParser {
    std::string mapPath;
    void loadMatrix(std::vector<std::vector<int>> matrix, YAML::Node& node);
    void editMap(Map* map);

 public:
    YamlParser();
    YamlParser(std::string& mapPath);
    void addMapName(std::string& mapName);
    std::vector<std::string> getMaps();
    void saveMap(Map* map);
    void getMap(Map* map);
};

#endif