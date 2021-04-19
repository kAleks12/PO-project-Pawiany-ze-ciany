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
#include <windows.h>

class Map {
private:
    static const int mapSize_ = 10;
    Field fields_ [mapSize_][mapSize_];
    static const bool isPytkaGrubas = true;
public:
    void spawn(Being *, int, int);
    void remove(int, int, int);
    bool isFieldFull(int, int);
    bool isFieldEmpty(int, int, int);
    static int getMapSize();
    Being * fieldGetHero(int, int, int);
    static int drawPos();
    void showField(int, int);
    void show();
};

#endif //PO_MAP_H
