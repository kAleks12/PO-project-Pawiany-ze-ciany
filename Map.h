#ifndef PO_MAP_H
#define PO_MAP_H

#include "Field.h"
#include "Being.h"
#include "Nomad.h"
#include "Knight.h"
#include "Slav.h"

#include <ctime>
#include <cstdlib>
#include <random>

class Map {
    static const int mapSize_ = 50;
    Field fields_ [mapSize_][mapSize_];
public:
    void spawn(Being *, int, int);
    void remove(int, int, int);
    void show();
    int drawPos();
    bool isFieldEmpty(int, int);
};

#endif //PO_MAP_H
