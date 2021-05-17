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
#include <vector>
#include <algorithm>

class Map {
private:
    static const int mapSize_ = 10;
    Field fields_ [mapSize_][mapSize_];
    std::list <Being*> allHeroes_;

public:
    void spawn(Being *, int, int);
    void changePos(Being*, int, int);
    void addHero(Being*);
    static int boundaryCheck(int);

    static void getItems(Field, Being*);
    static int getMapSize();
    int getX(Being *hero);
    int getY(Being *hero);
    int getPos(Being *hero);

    void showField(int, int);
    void show();
    bool isFieldFull(int, int);
    bool isPosEmpty(int, int, int);


    void move(Being *hero, int moveDirection);
    void encounter(Field &, int);
    void iteration();

    void removeHero(Being *);
};

#endif //PO_MAP_H
