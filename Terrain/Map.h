#ifndef PO_MAP_H
#define PO_MAP_H

#include "Field.h"
#include "../Troops/Being.h"
#include "../Troops/Nomad.h"
#include "../Troops/Knight.h"
#include "../Troops/Slav.h"

#include <ctime>
#include <cstdlib>
#include <random>
#include <windows.h>

class Map {
private:
    static const int mapSize_ = 10;
    Field fields_ [mapSize_][mapSize_];
public:
    void spawn(Being *, int, int);
    void remove(int, int, int);
    bool isFieldFull(int, int);
    static int getMapSize();
    Being * fieldGetHero(int, int, int);
    void showField(int, int);
    void show();
    void move(int, int, int, int, int);
    bool isPosEmpty(int, int, int);
};

#endif //PO_MAP_H
