#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void create_file(std::string& path) {
    // std::ofstream file;
    // file.open(path, std::ios::out);
    std::ofstream file(path,  std::ofstream::out);
    YAML::Node node = YAML::LoadFile(path);

    std::vector<std::vector<int>> matrix {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

    for (int i = 0; i < matrix.size(); i++) {
        YAML::Node v = YAML::Load("[]");
        for (int j = 0; j < matrix.size(); j++) {
            v.push_back(matrix[i][j]);
        }
        node["matrix"].push_back(v);
    }
    file << node;
    file.close();
}

std::vector<std::string> getMapNames(std::string& path) {
    /*Devuelve un vector con los mapas creados o lanza un error de tipo std::lenght_error*/
    try {
        YAML::Node node = YAML::LoadFile(path); // lo cargas
        std::vector<std::string> maps = node["maps"].as<std::vector<std::string>>();
        return maps;
    } catch(YAML::BadFile& e) {
        throw(std::length_error("No map has been created"));
    }
}

void edit_map(std::string& path, std::vector<std::vector<int>> map) {
    YAML::Node node = YAML::LoadFile(path); // lo cargas

    YAML::Node new_node;
    for (std::vector<int>& row : map) {
        YAML::Node matrix = YAML::Load("[]");
        for (int& tile : row) {
            matrix.push_back(tile);
        }
        new_node.push_back(matrix);
    }
    node["matrix"] = new_node;

    std::ofstream file(path,  std::ofstream::out); // lo creo
    file << node; // lo cargass
}


void loadMatrix(std::vector<std::vector<int>> matrix, YAML::Node& node) {
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

void editMap(std::string& mapPath) {
    YAML::Node node = YAML::LoadFile(mapPath);

    std::vector<std::vector<int>> matrix {{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}};
    loadMatrix(matrix, node);

    std::ofstream yaml_file(mapPath,  std::ofstream::out);
    yaml_file << node;
}

void saveMap(std::string& mapPath) {
    try { // es edición
        editMap(mapPath);
    } catch(YAML::BadFile& e) { // es creación
        std::ofstream yaml_file(mapPath,  std::ofstream::out);
        YAML::Node node = YAML::LoadFile(mapPath);

        node["width"] = 5;
        node["height"] = 5;
        node["players"] = 5;
        std::vector<std::vector<int>> matrix {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
        loadMatrix(matrix, node);

        yaml_file << node;
    }
}

void edit_maps_name(std::string& path, std::string mapName) {
    YAML::Node node;
    try {
        node = YAML::LoadFile(path); // lo cargas

        std::vector<std::string> maps = node["maps"].as<std::vector<std::string>>();
        maps.push_back(mapName);

        node["maps"] = maps; // lo modificas
    } catch(YAML::BadFile& e) {
        node["maps"].push_back(mapName);
    }
    std::ofstream file(path,  std::ofstream::out); // lo creo
    file << node; // lo cargass
}

void load_file(std::string& path) {
    YAML::Node node = YAML::LoadFile(path);

    std::vector<std::vector<int>> matrix = node["matrix"].as<std::vector<std::vector<int>>>();


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

void loading(std::string& map) {
    YAML::Node node = YAML::LoadFile(map);
    // std::cout << node["width"] << std::endl;
    int n = node["width"].as<int>();
    std::cout << n << std::endl;
}

int main() {
    std::string path = "pueba_yaml.yaml";
    std::string maps_names_path = "maps.yaml";
    std::string map = "prueba2.yaml";

    // create_yaml
    // create_file(path);

    // edit_yaml
    // std::string s("map4");
    // edit_maps_name(maps_names_path, s);

    // std::vector<std::string> v = getMapNames(maps_names_path);

    // std::vector<std::vector<int>> matrix {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    // edit_map(path, matrix);

    // saveMap(map);

    // loading(map);

    // load a yaml
    std::string p("hila.yaml");
    load_file(p);

    return 0;
}