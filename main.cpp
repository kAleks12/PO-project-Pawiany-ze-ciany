//
//  Created by
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
//#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

#include "Nomad.h"
#include "Knight.h"
#include "Slav.h"
#include "Viking.h"
#include "Map.h"

void move(int pos, int xFrom, int yFrom, int xWhere, int yWhere, Map & adventureMap){
    if((!adventureMap.isFieldFull(xWhere, yWhere))&&(!adventureMap.isFieldEmpty(xFrom, yFrom, pos))){
        if(adventureMap.isFieldEmpty(xWhere, yWhere, 0)) {
            adventureMap.spawn(adventureMap.fieldGetHero(xFrom, yFrom, 0), xWhere, yWhere);
            adventureMap.fieldGetHero(xFrom, yFrom, 0)->setCoords(xWhere, yWhere);
        }
        else {
            adventureMap.spawn(adventureMap.fieldGetHero(xFrom, yFrom, 1), xWhere, yWhere);
            adventureMap.fieldGetHero(xFrom, yFrom, 1)->setCoords(xWhere, yWhere);
        }
        adventureMap.remove(xFrom, yFrom, pos);
    }
    else
        //std::cout << adventureMap.isFieldFull(xWhere, yWhere) << " " << adventureMap.isFieldEmpty(xFrom, yFrom, pos) << std::endl;
        std::cout << "Where is full, or From is empty" << std::endl;
    //ZMIENIC KORDY POSTACI!!!!!!!!!!!!!!!!!!!!!!!
}

template <typename ClassName> inline void generateClassObject(std::string name, Map & map){
    int tmpXPos, tmpYPos;
    auto tmp = new ClassName(name);
    do {
        tmpXPos = Map::drawPos();
        tmpYPos = Map::drawPos();
    } while(map.isFieldFull(tmpXPos, tmpYPos));
    tmp -> setCoords(tmpXPos,tmpYPos);
    map.spawn(tmp, tmpXPos, tmpYPos);
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

void generateMap(Map & adventureMap){
    std::ifstream fNames("names.txt");
    std::mt19937 engine {std::random_device{}()};
    std::uniform_int_distribution <int> limRange(1, 99);
    srand(time(nullptr));

    int numOfObj = Map::getMapSize()*2 + 400;
    int numOfSlavs = 0;
    int numOfNomads = 0;
    int numOfKnights = 0;
    int numOfVikings = 0;

    //Getting user input
    while((numOfObj > Map::getMapSize()*2) || (numOfObj > 400) || (numOfObj <= 0))  {
        std::cout << "Give me amount of objects to create: ";
        std::cin >> numOfObj;
    }

    //Checking if entered number is too small to draw
    switch(numOfObj){
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
            while(rand() % 15 != 10){
                numOfSlavs = limRange(engine);
                numOfNomads = limRange(engine);
                numOfVikings = limRange(engine);
                numOfKnights = limRange(engine);
            }
            adjustNumberOfObjects(numOfSlavs, numOfNomads, numOfVikings, numOfKnights, (numOfNomads + numOfSlavs + numOfKnights + numOfVikings) - numOfObj);
            break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    std::cout <<"\nList of objects -> Slavs: " << numOfSlavs << "; Nomads:  " << numOfNomads << "; Vikings:  " << numOfVikings << "; Knights:  " <<  numOfKnights << ";\tTotal: " << numOfNomads + numOfSlavs + numOfKnights + numOfVikings << "\n";

    if(fNames.good()) {
        std::string name;
        //Creating and spawning Slav objects

        for (int i = 0; i < numOfSlavs; i++) {
            fNames >> name;
            generateClassObject <Slav> (name, adventureMap);
            //std::cout << "Done " << i << " out of " << numOfSlavs << "\n";
        }
        std::cout << "\nDone " << numOfSlavs << " Slavs!\n";

        // Creating and spawning Nomad objects

        for (int i = 0; i < numOfNomads; i++) {
            fNames >> name;
            generateClassObject <Nomad> (name, adventureMap);
            //std::cout << "Done " << i << " out of " << numOfNomads << "\n";
        }
        std::cout << "Done " << numOfNomads << " Nomads!\n";

        // Creating and spawning Viking objects

        for (int i = 0; i < numOfVikings; i++) {
            fNames >> name;
            generateClassObject <Viking> (name, adventureMap);
            //std::cout << "Done " << i << " out of " << numOfVikings << "\n";
        }
        std::cout << "Done " << numOfVikings << " Vikings!\n";

        // Creating and spawning Knight objects

        for (int i = 0; i < numOfKnights; i++) {
            fNames >> name;
            generateClassObject <Knight> (name, adventureMap);
            //std::cout << "Done " << i << " out of " << numOfKnights << "\n";
        }
        std::cout << "Done " << numOfKnights << " Knights!\n\n";
        fNames.close();
    }
    else {
        std::cout << "File \"names.txt\" not found" << std::endl;
    }
}

int main() {
    Map adventureMap;
    generateMap(adventureMap);

    adventureMap.show();
}