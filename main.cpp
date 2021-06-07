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


#include "Terrain/Map.h"

inline std::string drawName();
inline int drawPos();
template <typename ClassName> ClassName* generateClassObject(std::string name, Map & map, int tribe);
void generateItem(Map & map, int itemId);
inline void adjustNumberOfObjects( int & numOfObjects1, int & numOfObjects2, int & numOfObjects3, int & numOfObjects4, int difference);
void fillMap(Map & adventureMap);

std::mt19937 engine{std::random_device{}()};

int main() {

    Map adventureMap;

    fillMap(adventureMap);

    adventureMap.show();

    while(adventureMap.numOfTribes() > 1) {//simulation goes until there will be only one tribe alive
        std::cout<<adventureMap.numOfTribes()<<std::endl;
        adventureMap.iteration();
        //system("Pause");
        //Sleep(2000);
    }

    std::cout<<adventureMap.numOfTribes()<<std::endl;
    std::cout<<"\n\t\t\t\t\tTHE SIMULATION IS OVER\n";

    int victoriousTribe;//showing details of simulation and stuff

    for(int i=0; i<4; i++){
        if(adventureMap.isThisTribeAlive(i)){
            std::cout<<"Tribe number "<< i <<" Has won\n\n";
            victoriousTribe = i;
        }
    }

    for(int i=0; i<4; i++)
        std::cout << "Tribe number " << i << " kills: " << adventureMap.returnTribeKills(i) << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    int listSize = adventureMap.getListSize();

        adventureMap.showAndKillList(victoriousTribe);



}

inline int drawPos() {//generating random position on the map
    std::uniform_int_distribution<int> posRange(0, (sqrt(Map::getMapSize())-1));
    int randomNum;
    randomNum = posRange(engine);
    return randomNum;
}

inline std::string drawName(){//generating names

    std::ifstream fNames("names.txt");

    if(fNames.good()) {
        std::uniform_int_distribution <int> namesRange(1, 92);
        std::string name;
        int pos = namesRange(engine);

        while (pos-- != 0)
            getline(fNames, name);

        fNames.close();

        return name;
    }
    else return "File not found!";
}

template <typename ClassName> ClassName* generateClassObject(std::string name, Map & map, int tribe){//spawning new heroes
    int tmpXPos, tmpYPos;
    auto tmp = new ClassName(name, tribe, engine);
    do {
        tmpXPos = drawPos();
        tmpYPos = drawPos();
    } while (map.isFieldFull(tmpXPos, tmpYPos));
    map.spawn(tmp, tmpXPos, tmpYPos);
    return tmp;
}

void generateItem(Map & map, int itemId)//spawning items on the map
{
    int tmpX, tmpY;
    do {
        tmpX = drawPos();
        tmpY = drawPos();
    } while(map.isFieldFull(tmpX, tmpY));

    map.addItem(tmpX, tmpY, itemId);
}

inline void adjustNumberOfObjects( int & numOfObjects1, int & numOfObjects2, int & numOfObjects3, int & numOfObjects4, int difference)
{//OHMYGOD no clue whats happening here. Simply amounts of heroes and classes are being adjusted
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

void fillMap(Map & adventureMap){//filling map
    std::uniform_int_distribution <int> heroesRange(1, 99);
    std::uniform_int_distribution <int> itemsRange(1, 9);
    int numOfItems = 0;

    for(int j=0;j<4;j++) {//each tribe
        int numOfObj = Map::getMapSize() * 2 + 400;

        int numOfSlavs = 0;
        int numOfNomads = 0;
        int numOfKnights = 0;
        int numOfVikings = 0;

        //Getting user input
        while ((numOfObj > Map::getMapSize() / 2)  || (numOfObj <= 0)) {
            /*std::cout << "GEnter number of objects to create: ";
            std::cin >> numOfObj;
            std::cout << "Enter number of items to create"
            std::cin >> numOfItems;*/
            numOfObj = 10;
            numOfItems = 10;
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
                numOfSlavs = heroesRange(engine);
                numOfNomads = heroesRange(engine);
                numOfVikings = heroesRange(engine);
                numOfKnights = heroesRange(engine);
                adjustNumberOfObjects(numOfSlavs, numOfNomads, numOfVikings, numOfKnights,
                                      (numOfNomads + numOfSlavs + numOfKnights + numOfVikings) - numOfObj);
                break;
        }
        /*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        std::cout << "\nList of objects -> Slavs: " << numOfSlavs << "; Nomads:  " << numOfNomads << "; Vikings:  "
                  << numOfVikings << "; Knights:  " << numOfKnights << ";\tTotal: "
                  << numOfNomads + numOfSlavs + numOfKnights + numOfVikings << "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);*/

        //Creating and spawning Slav objects

        for (int i = 0; i < numOfSlavs; i++) {
            adventureMap.addHero(generateClassObject<Slav>(drawName(), adventureMap,j));
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfSlavs << "\n";
        }
        //std::cout << "\nDone " << numOfSlavs << " Slavs!\n";

        for (int i = 0; i < numOfNomads; i++) {
            adventureMap.addHero(generateClassObject<Nomad>(drawName(), adventureMap,j));
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfNomads << "\n";
        }
        //std::cout << "Done " << numOfNomads << " Nomads!\n";

        for (int i = 0; i < numOfVikings; i++) {
            adventureMap.addHero(generateClassObject<Viking>(drawName(), adventureMap,j));
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfVikings << "\n";
        }
        //std::cout << "Done " << numOfVikings << " Vikings!\n";

        // Creating and spawning Knight objects

        for (int i = 0; i < numOfKnights; i++) {
            adventureMap.addHero(generateClassObject<Knight>(drawName(), adventureMap,j));
            //tmp.show();
            //std::cout << "Done " << i << " out of " << numOfKnights << "\n";
        }
        //std::cout << "Done " << numOfKnights << " Knights!\n\n";
    }
    for (int i = 0; i < numOfItems; i++) {
        generateItem(adventureMap, itemsRange(engine));
    }

}

