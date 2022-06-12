#include "yaml_parser.h"
#include "map.h"

#include <iostream>
#include <vector>

int main() {
    std::string path("/home/florencia/taller/repo_grupo/src/prueba2.yaml");
    YamlParser parser(path);
    Map map;
    parser.getMap(&map);
    std::cout << map.getWidth();
    std::cout << map.getHeight();
    std::cout << map.getNPlayers();
    std::vector<std::vector<int>> matrix = map.getMap();
    std::cout << "[";
    for (int i = 0; i < matrix.size(); i ++) {
        std::cout << "[";
        for (int j = 0; j < matrix[i].size(); j ++) {
            if (j == (matrix[i].size() -1)) {
                std::cout << matrix[i][j];
                continue;
            }
            std::cout << matrix[i][j] << ", ";
        }
        if (i == (matrix.size() -1)) {
            std::cout << "]" ;
            continue;
        }
        std::cout << "]" << ", ";
    }
    std::cout << "]";
    std::cout << std::endl;
}