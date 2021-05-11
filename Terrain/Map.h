#ifndef PO_MAP_H
#define PO_MAP_H

#include "Field.h"
#include "../Troops/Being.h"
#include "../Troops/Nomad.h"
#include "../Troops/Knight.h"
#include "../Troops/Slav.h"
#include "../Troops/Viking.h"

#include <ctime>
#include <cstdlib>
#include <random>
#include <windows.h>
#include <list>
#include <time.h>

class Map {
private:
    static const int mapSize_ = 10;
    Field fields_ [mapSize_][mapSize_];
    std::list <Being*> allHeroes_;

public:
    void spawn(Being *, int, int);
    void remove(int, int, int);
    bool isFieldFull(int, int);
    static int getMapSize();
    Being * fieldGetHero(int, int, int);
    void showField(int, int);
    void show();
    void changePos(int, int, int, int, int);
    bool isPosEmpty(int, int, int);
    void addHero(Being*);

    void move(Being *hero, int moveDirection);
    int getX(Being *hero);
    int getY(Being *hero);
    int getPos(Being *hero);
    static void getItems(Field, Being*);
    void encounter(Field &, int);
    void iteration();
    int boundryCheck(int);
};

#endif //PO_MAP_H
