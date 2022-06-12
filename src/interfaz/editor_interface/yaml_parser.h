#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include "map.h"

#define MAPS "/home/florencia/taller/repo_grupo/src/interfaz/editor_interface/maps/maps.yaml"
#define ITEMS "/home/florencia/taller/repo_grupo/src/interfaz/editor_interface/maps/map_items.yaml"
#define MAPS_ROUTE "/home/florencia/taller/repo_grupo/src/interfaz/editor_interface/maps/"

class YamlParser {
    std::string mapPath;
    void loadMatrix(std::vector<std::vector<int>> matrix, YAML::Node& node);
    void editMap(Map* map);

 public:
    YamlParser();
    YamlParser(std::string& mapPath);
    void addMapName(std::string& mapName);
    std::vector<std::string> getMaps();
    std::map<std::string, std::string> getItems(std::string& type);
    std::map<int, std::vector<std::string>> getTranslator();
    int getItemId(std::string parentType, std::string type);
    void saveMap(Map* map);
    void getMap(Map* map);
};

#endif
