#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <vector>
#include <string>
#include <map>
#include "map.h"

#define MAPS "../server/maps/maps.yaml"
#define ITEMS "../editor/maps/map_items.yaml"
#define MAPS_ROUTE "../server/maps/"

class YamlParser {
    std::string mapPath;
    void loadMatrix(std::vector<std::vector<int>> matrix,
                    YAML::Node& node, const std::string& key);
    void editMap(Map* map);

 public:
    YamlParser();
    explicit YamlParser(const std::string& mapPath);
    void addMapName(const std::string& mapName);
    std::vector<std::string> getMaps();
    std::map<std::string, std::string> getItems(const std::string& type);
    std::map<int, std::vector<std::string>> getTranslator();
    int getItemId(const std::string& parentType, const std::string& type);
    void saveMap(Map* map);
    void getMap(Map* map);
};

#endif
