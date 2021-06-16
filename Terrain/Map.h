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

#ifndef SCREEN_OUTPUT
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
    void spawn(Being *, int, int); //adding heroes to the specific field on the map
    void addToList(Being*); //adding heroes to the heroes list
    void cleanList(); //deleting dead heroes from the list
    void addItem(int, int, int); //adding item to the specific field on the map
    void deactivate();

    //HEROES SETTERS
    void addTribeKill(int);
    static void pickItems(Field, Being*); //picking up objects from the certain field by hero

    //MAP GETTERS
    int getTribeKills(int);
    static int getMapSize();
    bool getStatus(); //has certain simulation already finished
    int heroesOnMap(); //how many alive heroes are there on the map
    int numOfTribes(); //how many tribes there are
    bool isFieldFull(int, int);
    bool isPosEmpty(int, int, int);
    bool isTribeAlive(int);

    //HEROES GETTERS
    int getX(Being *hero); //seeking trough an entire map to find certain hero, and return its coords
    int getY(Being *hero); //seeking trough an entire map to find certain hero, and return its coords
    int getPos(Being *hero); //seeking trough an entire map to find certain hero, and return its position on the field

    //PRINTERS
    static void goToXY(int, int); //sets cursor at certain position, used for clearing screen
    static void clearScreen(int, int); //clear screen
    void printList(); //used for debugging
    void show(); //printing map
    void generateSummary(int, float); //simulations summary
    void generateKillList(int); //printing entire list of tribe that has won (only alive heroes)

    //RUNNING SIMULATION
    void move(Being *hero, int moveDirection); //movement section
    void planMove(int, int, int, int, int *, int *); //tiny movement mainEngine
    static int bCheck(int); //checking whether action isn't trying to reach outside map
    void changePos(Being*, int, int); //relocating heroes from field to another field
    void encounter(Field &, int); //interaction with other heroes
    void iteration(); //iteration engine
};

#endif //PO_MAP_H
