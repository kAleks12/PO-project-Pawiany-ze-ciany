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
    int tribeKills[4]={0, 0, 0, 0};

public:
    void spawn(Being *, int, int);
    void addHero(Being*);
    void addItem(int, int, int);
    static void getItems(Field, Being*);
    void changePos(Being*, int, int);
    void cleanList();
    static int bCheck(int);
    void addTribeKill(int);
    int returnTribeKills(int);

    static int getMapSize();
    int getListSize();
    int numOfTribes();
    int getX(Being *hero);
    int getY(Being *hero);
    int getPos(Being *hero);
    bool isTribeAlive(int);

    [[maybe_unused]] void showField(int, int);
    void showAndKillList(int);
    void show();

    void move(Being *hero, int moveDirection);
    void encounter(Field &, int);
    void iteration();
    void seekForInteraction(int, int, int, int, int *, int *);

    bool isFieldFull(int, int);
    bool isPosEmpty(int, int, int);
};

#endif //PO_MAP_H
