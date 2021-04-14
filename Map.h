#ifndef PO_MAP_H
#define PO_MAP_H
#include "Field.h"
#include "Being.h"

class Map {
    //Field map[100][100];
public:
    void spawn(Being, int, int);

    void remove();

};

#endif //PO_MAP_H
