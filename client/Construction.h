#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__


#include <string>

// Esto parece no usarse, no tiene constructor ni se pueden setear los atributos...
class Construction {
    int type;
    int x;
    int y;
    std::string name;
    public:
    int getType();
    int getPosX();
    int getPosY();
};

#endif /*__CONSTRUCTION_H__*/
