//
//  Created by
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <windows.h>

#include "Troops/Tribe.h"
#include "Terrain/Map.h"

inline int drawPos() {
    std::random_device rd;
    std::mt19937 randomSeed(rd());
    std::uniform_int_distribution<int> posRange(0, (sqrt(Map::getMapSize())-1));
    int randomNum;
    Sleep(1000);
    while(rand () % 15 != 10) {
        randomNum = posRange(randomSeed);
    }
    return randomNum;
}

template <typename ClassName> inline ClassName* generateClassObject(std::string name, Map & map, Tribe & currentTribe){
    int tmpXPos, tmpYPos;
    auto tmp = new ClassName(name);
    do {
        tmpXPos = drawPos();
        tmpYPos = drawPos();
    } while(map.isFieldFull(tmpXPos, tmpYPos));
    tmp -> setCoords(tmpXPos,tmpYPos);
    map.spawn(tmp, tmpXPos, tmpYPos);
    return tmp;
}

inline void adjustNumberOfObjects( int & numOfObjects1, int & numOfObjects2, int & numOfObjects3, int & numOfObjects4, int difference)
{
    if(difference < 0) {
        difference = -(difference);

        while (difference > 0) {
            difference -= numOfObjects1 / 2;
            numOfObjects1 += numOfObjects1 / 2;
            if (difference <= 0) break;
            difference -= numOfObjects2 / 2;
            numOfObjects2 += numOfObjects2 / 2;
            if (difference <= 0) break;
            difference -= numOfObjects3 / 2;
            numOfObjects3 += numOfObjects3 / 2;
            if (difference <= 0) break;
            difference -= numOfObjects4 / 2;
            numOfObjects4 += numOfObjects4 / 2;
        }


        if(difference < 0 && numOfObjects4 + difference >=0) {
            numOfObjects4 += difference;
            difference = 0;
        }
        else if(difference < 0 && numOfObjects3 + difference >=0) {
            numOfObjects3 += difference;
            difference = 0;
        }
        else if(difference < 0 && numOfObjects2 + difference >=0) {
            numOfObjects2 += difference;
            difference = 0;
        }
        else if(difference < 0 && numOfObjects1 + difference >=0) {
            numOfObjects1 += difference;
            difference = 0;
        }
        //Przypadek kiedy nie można odjąć róznicy od jednej liczby

        if(difference < 0 && numOfObjects4 + difference < 0) {
            difference += numOfObjects4;
            numOfObjects4 = 0;
        }
        if(difference < 0 && numOfObjects3 + difference < 0) {
            difference += numOfObjects3;
            numOfObjects3 = 0;
        }
        else if(difference < 0 && numOfObjects2 + difference < 0) {
            difference += numOfObjects2;
            numOfObjects2 = 0;
        }
        else if(difference < 0 && numOfObjects1 + difference < 0) {
            difference += numOfObjects1;
            numOfObjects1 = 0;
        }
    }
    else {
        while (difference > 0) {
            difference -= numOfObjects4 / 2;
            numOfObjects4 -= numOfObjects4 / 2;
            if (difference <= 0) break;
            difference -= numOfObjects3 / 2;
            numOfObjects3 -= numOfObjects3 / 2;
            if (difference <= 0) break;
            difference -= numOfObjects2 / 2;
            numOfObjects2 -= numOfObjects2 / 2;
            if (difference <= 0) break;
            difference -= numOfObjects1 / 2;
            numOfObjects1 -= numOfObjects1 / 2;
        }

        // Case when it is possible to apply final correction to one of the numbers

        if(difference < 0 && numOfObjects4 + difference >=0) {
            numOfObjects4 += -(difference);
            difference = 0;
        }
        else if(difference < 0 && numOfObjects3 + difference >=0) {
            numOfObjects3 += -(difference);
            difference = 0;
        }
        else if(difference < 0 && numOfObjects2 + difference >=0) {
            numOfObjects2 += -(difference);
            difference = 0;
        }
        else if(difference < 0 && numOfObjects1 + difference >=0) {
            numOfObjects1 += -(difference);
            difference = 0;
        }
    }
}

void fillMap(Map & adventureMap, Tribe & currentTribe){
    std::ifstream fNames("names.txt");
    std::mt19937 engine {std::random_device{}()};
    std::uniform_int_distribution <int> limRange(1, 99);
    srand(time(nullptr));

    int numOfObj = Map::getMapSize() * 2 + 400;
    int numOfSlavs = 0;
    int numOfNomads = 0;
    int numOfKnights = 0;
    int numOfVikings = 0;

    //Getting user input
    while((numOfObj > Map::getMapSize()*2) || (numOfObj > 100) || (numOfObj <= 0))  {
        //std::cout << "Give me amount of objects to create: ";
        //std::cin >> numOfObj;
        numOfObj = 5;
    }

    //Checking if entered number is too small to draw
    switch (numOfObj) {
        case 1:
            numOfSlavs++;
            break;
        case 2:
            numOfSlavs++;
            numOfNomads++;
            break;
        case 3:
            numOfSlavs++;
            numOfNomads++;
            numOfVikings++;
            break;
        case 4:
            numOfSlavs++;
            numOfNomads++;
            numOfVikings++;
            numOfKnights++;
            break;
        default:
            while (rand() % 15 != 10) {
                numOfSlavs = limRange(engine);
                numOfNomads = limRange(engine);
                numOfVikings = limRange(engine);
                numOfKnights = limRange(engine);
            }
            adjustNumberOfObjects(numOfSlavs, numOfNomads, numOfVikings, numOfKnights,
                                  (numOfNomads + numOfSlavs + numOfKnights + numOfVikings) - numOfObj);
            break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    std::cout << "\nList of objects -> Slavs: " << numOfSlavs << "; Nomads:  " << numOfNomads << "; Vikings:  "
              << numOfVikings << "; Knights:  " << numOfKnights << ";\tTotal: "
              << numOfNomads + numOfSlavs + numOfKnights + numOfVikings << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    std::string name;
    //Creating and spawning Slav objects

        for (int i = 0; i < numOfSlavs; i++) {
            fNames >> name;
            Slav tmp = *(generateClassObject <Slav> (name, adventureMap, currentTribe));
            currentTribe.addSlav(tmp);
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfSlavs << "\n";
        }
        std::cout << "\nDone " << numOfSlavs << " Slavs!\n";

        for (int i = 0; i < numOfNomads; i++) {
            fNames >> name;
            Nomad tmp = *(generateClassObject <Nomad> (name, adventureMap, currentTribe)) ;
            currentTribe.addNomad(tmp);
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfNomads << "\n";
        }
        std::cout << "Done " << numOfNomads << " Nomads!\n";

        for (int i = 0; i < numOfVikings; i++) {
            fNames >> name;
            Viking tmp = *(generateClassObject <Viking> (name, adventureMap, currentTribe)) ;
            currentTribe.addViking(tmp);
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfVikings << "\n";
        }
        std::cout << "Done " << numOfVikings << " Vikings!\n";

        // Creating and spawning Knight objects

        for (int i = 0; i < numOfKnights; i++) {
            fNames >> name;
            Knight tmp = *(generateClassObject <Knight> (name, adventureMap, currentTribe));
            currentTribe.addKnight(tmp);
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfKnights << "\n";
        }
        std::cout << "Done " << numOfKnights << " Knights!\n\n";
        fNames.close();
}

int main() {

    Tribe northEast;
    Tribe southEast;
    Tribe northWest;
    Tribe southWest;

    Map adventureMap;

    fillMap(adventureMap, northEast);
    fillMap(adventureMap, southEast);
    fillMap(adventureMap, northWest);
    fillMap(adventureMap, southWest);

    northEast.show();
    southEast.show();
    northWest.show();
    southWest.show();

    adventureMap.show();

    while(true){
        int x1, y1, x2, y2, pos;
        std::cout << "Podaj podaj koordynaty pola i pozycje (x,y,pos) z której chcesz przeniesc istote, oraz kooordynaty pola (x,y) gdzie chcesz ja przeniesc :) \n";
        std::cin >> x1 >> y1 >> pos >> x2 >> y2;
        adventureMap.move(x1,y1,pos,x2,y2);
        adventureMap.show();
    }
}