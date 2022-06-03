#include <string>
#include <iostream>
#include <sstream>

#include "server_terrain_map.h"
#include "server_units.h"


int main() {
    std::string linea;
    TerrainMap ter({{1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 0, 1, 1},
                  {2, 2, 2, 1, 2, 2, 0, 0, 0, 1, 2, 2, 1, 1, 1, 1, 0, 1, 1},
                  {1, 2, 1, 1, 2, 2, 0, 0, 0, 1, 2, 2, 2, 1, 1, 1, 0, 0, 0},
                  {1, 1, 1, 1, 2, 3, 3, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1},
                  {1, 1, 1, 1, 3, 3, 3, 1, 1, 1, 2, 2, 2, 1, 0, 0, 0, 1, 1},
                  {1, 1, 1, 2, 3, 3, 3, 0, 1, 1, 2, 2, 2, 2, 0, 0, 1, 1, 1},
                  {1, 1, 1, 3, 3, 1, 1, 0, 2, 1, 2, 2, 2, 2, 0, 1, 1, 2, 2},
                  {1, 1, 1, 3, 1, 1, 1, 0, 0, 1, 2, 2, 2, 2, 0, 1, 2, 2, 1},
                  {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 2, 2, 2, 2, 0, 1, 2, 1, 1}});
    std::cout << "Ingrese unidad (i - infanteria, v - vehiculo): ";
    getline(std::cin, linea);
    coor_t dims = ter.getDims();
    coor_t act(dims.first - 1, 0);
    coor_t dest(0, dims.second - 1);
    ter.print(act, dest);
    Unit* unit;
    if (linea == "i") {
        unit = new Infantry(act, ter);
    } else {
        unit = new Vehicle(act, ter);
    }
    while (getline(std::cin, linea) && act != dest && linea != "q") {
        if (linea != "") {
            int x, y;
            std::stringstream stream_linea;
            stream_linea << linea;
            stream_linea >> x >> std::ws >> y;
            dest = coor_t(x, y);
        }
        unit->processMove(dest);
        act = unit->getPosition();
        ter.print(act, dest);
    } 
    delete unit;
    return 0;
}
