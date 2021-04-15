#ifndef PO_MAP_H
#define PO_MAP_H
#include "Field.h"
#include "Being.h"
#include "Southern_Warrior.h"
#include "Knight.h"
#include "Slav.h"

class Map {
    static const int mapSize = 50;
    Field fields [mapSize][mapSize];
public:
    void spawn(Being *, int, int);
    void remove(int, int, int);

    void showMap();
};

#endif //PO_MAP_H
