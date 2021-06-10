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
#include <fstream>

class Map {
private:
    std::fstream summary_;
    std::string name_ ;

    static const int mapSize_ = 10;
    static int numOfMapsCreated;
    int iterationCount_ = 0;
    int tribeKills[4]={0, 0, 0, 0};

    bool isFinished_ = false;

    Field fields_ [mapSize_][mapSize_];
    std::list <Being*> allHeroes_;

public:
    Map();
    void spawn(Being *, int, int);
    void addHero(Being*);
    void addItem(int, int, int);
    static void getItems(Field, Being*);
    void changePos(Being*, int, int);
    void cleanList();
    static int bCheck(int);
    void addTribeKill(int);
    int getTribeKills(int);

    static int getMapSize();
    int numOfTribes();
    int getX(Being *hero);
    int getY(Being *hero);
    int getPos(Being *hero);
    int heroesOnMap();
    bool getStatus();

    void generateKillList(int);
    void show();

    void move(Being *hero, int moveDirection);
    void encounter(Field &, int);
    void iteration();
    void seekForInteraction(int, int, int, int, int *, int *);
    void generateSummary();

    static void goToXY(int, int);
    static void clearScreen(int, int);

    bool isFieldFull(int, int);
    bool isPosEmpty(int, int, int);
    bool isTribeAlive(int);
    void deactivateMap();
};

#endif //PO_MAP_H
