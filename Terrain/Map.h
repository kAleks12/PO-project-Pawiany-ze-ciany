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
    //static std::ofstream simSummary_;
    std::fstream summary_;
    std::string name_ ;

#ifdef SCREEN_OUTPUT
    static const int mapSize_ = 10;
#endif

#ifdef EXCEL_OUTPUT
    static const int mapSize_ = 50;
#endif

    static int numOfMapsCreated;
    int iterationCount_ = 0;
    int tribeKills[4]={0, 0, 0, 0};

    bool isFinished_ = false;

    Field fields_ [mapSize_][mapSize_];
    std::list <Being*> allHeroes_;

public:
    //CONSTRUCTOR
    Map();

    //SETTERS
    void spawn(Being *, int, int);
    void addToList(Being*);
    void cleanList();
    void addItem(int, int, int);
    void deactivate();

    //HEROES SETTERS
    void addTribeKill(int);
    static void getItems(Field, Being*);

    //MAP GETTERS
    int getTribeKills(int);
    static int getMapSize();
    bool getStatus();
    int heroesOnMap();
    int numOfTribes();
    bool isFieldFull(int, int);
    bool isPosEmpty(int, int, int);
    bool isTribeAlive(int);

    //HEROES GETTERS
    int getX(Being *hero);
    int getY(Being *hero);
    int getPos(Being *hero);

    //PRINTERS
    static void goToXY(int, int);
    static void clearScreen(int, int);
    void printList();
    void show();
    void generateSummary(int, float);
    void generateKillList(int);

    //RUNNING SIMULATION
    void move(Being *hero, int moveDirection);
    void planMove(int, int, int, int, int *, int *);
    static int bCheck(int);
    void changePos(Being*, int, int);
    void encounter(Field &, int);
    void iteration();
};

#endif //PO_MAP_H
