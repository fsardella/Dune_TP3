#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__


#include <string>


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
