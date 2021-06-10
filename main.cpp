//
//  Created by
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
#include <random>
#include <string>
#include <vector>


#include "Terrain/Map.h"

void createMaps(std::vector <Map*> &, int);
inline std::string drawName();
inline int drawPos();
template <typename ClassName> ClassName* generateHeroes(std::string , Map & , int );
void generateItem(Map & , int );
inline void adjustNumberOfObjects( int & , int & , int & , int & , int );
void fillMap(Map & , int, int);
bool isIntiger(std::string);

std::mt19937 mainEngine{std::random_device{}()};




int main() {

    std::vector <Map*> maps;

    std::string strAmountOfTroops = "1";
    std::string strAmountOfMaps = "1";
    std::string strAmountOfItems = "1";
    int amountOfTroops = 1;
    int amountOfMaps = 1;
    int amountOfItems = 1;

    inputAmountMaps:

    std::cout<<"How many maps should there be?\n";
    std::cin>>strAmountOfMaps;

    if(isIntiger(strAmountOfMaps) && (amountOfMaps > 0))
        amountOfMaps = stoi(strAmountOfMaps);
    else{
        std::cout<<"invalid number\n";
        goto inputAmountMaps;
    }

    inputAmountTroops:

    std::cout<<"How many troops in each tribe should there be?\n";
    std::cin>>strAmountOfTroops;

    if(isIntiger(strAmountOfTroops)) {
        amountOfTroops = stoi(strAmountOfTroops);
        if ((amountOfTroops > Map::getMapSize() / 2) || (amountOfTroops <= 0)){
            std::cout<<"number is to high or low\n";
            goto inputAmountTroops;
        }
    }
    else{
        std::cout<<"invalid number\n";
        goto inputAmountTroops;
    }

    inputAmountItems:

    std::cout<<"How many items on map should there be?\n";
    std::cin>>strAmountOfItems;

    if(isIntiger(strAmountOfItems))
        amountOfTroops = stoi(strAmountOfItems);
    else{
        std::cout<<"invalid number\n";
        goto inputAmountItems;
    }

    createMaps(maps, amountOfMaps);

    for(auto & map: maps){
        fillMap(*map, amountOfTroops, amountOfItems);
    }

    int i = 0;
    while(!maps.empty()){
        for(auto & map: maps){
            if(map -> numOfTribes() > 1){
                map->goToXY(0, 0);
                map->clearScreen(0,81);
                map->goToXY(0, 0);
                std::cout << "Iteration of map no: " << i % maps.size() << std::endl;
                map->iteration();
                map->goToXY(0, 20);
                system("pause");
            }
            else{
                map -> goToXY(0,0);
                map -> clearScreen(40,120);
                map -> goToXY(0,0);
                map->generateSummary();
                map -> deactivateMap();
                system("pause");
                for (auto it = maps.begin(); it != maps.end(); ) {
                    if ((*it)->getStatus()) {
                        it = maps.erase(it);
                    } else {
                        ++it;
                    }
                }
            }
            i++;
        }
    }
}






inline int drawPos() {  //generating random position on the map
    std::uniform_int_distribution<int> posRange(0, (sqrt(Map::getMapSize())-1));
    int randomNum;

    randomNum = posRange(mainEngine);

    return randomNum;
}

inline std::string drawName(){  //generating names

    std::ifstream fNames("names.txt");

    if(fNames.good()) {
        std::uniform_int_distribution <int> namesRange(1, 94);
        std::string name;

        int pos = namesRange(mainEngine);

        while (pos-- != 0)
            getline(fNames, name);

        fNames.close();

        return name;
    }
    else return "File not found!";
}

template <typename ClassName> ClassName* generateHeroes(std::string name, Map & map, int tribe){   //spawning new heroes
    int tmpXPos, tmpYPos;

    auto tmp = new ClassName(name, tribe, mainEngine);
    do {
        tmpXPos = drawPos();
        tmpYPos = drawPos();
    } while (map.isFieldFull(tmpXPos, tmpYPos));

    map.spawn(tmp, tmpXPos, tmpYPos);

    return tmp;
}

void generateItem(Map & map, int itemId)    //spawning items on the map
{
    int tmpX, tmpY;
    do {
        tmpX = drawPos();
        tmpY = drawPos();
    } while(map.isFieldFull(tmpX, tmpY));

    map.addItem(tmpX, tmpY, itemId);
}

inline void adjustNumberOfObjects( int & numOfObjects1, int & numOfObjects2, int & numOfObjects3, int & numOfObjects4, int difference)
{   //OHMYGOD no clue whats happening here. Simply amounts of heroes and classes are being adjusted
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

void fillMap(Map & adventureMap, int amountOfTroops, int amountOfobjects){   //filling map
    std::uniform_int_distribution <int> heroesRange(1, 99);
    std::uniform_int_distribution <int> itemsRange(1, 9);
    int numOfItems = 0;

    for(int j=0;j<4;j++) {  //each tribe
        int numOfObj;

        int numOfSlavs = 0;
        int numOfNomads = 0;
        int numOfKnights = 0;
        int numOfVikings = 0;


            numOfObj = amountOfTroops;
            numOfItems = amountOfobjects;

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
                numOfSlavs = heroesRange(mainEngine);
                numOfNomads = heroesRange(mainEngine);
                numOfVikings = heroesRange(mainEngine);
                numOfKnights = heroesRange(mainEngine);
                adjustNumberOfObjects(numOfSlavs, numOfNomads, numOfVikings, numOfKnights,
                                      (numOfNomads + numOfSlavs + numOfKnights + numOfVikings) - numOfObj);
                break;
        }
/*
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        std::cout << "\nList of objects -> Slavs: " << numOfSlavs << "; Nomads:  " << numOfNomads << "; Vikings:  "
                  << numOfVikings << "; Knights:  " << numOfKnights << ";\tTotal: "
                  << numOfNomads + numOfSlavs + numOfKnights + numOfVikings << "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
*/

        //Creating and spawning Slav objects

        for (int i = 0; i < numOfSlavs; i++) {
            adventureMap.addHero(generateHeroes<Slav>(drawName(), adventureMap, j));
        }

        // Creating and spawning Nomad objects

        for (int i = 0; i < numOfNomads; i++) {
            adventureMap.addHero(generateHeroes<Nomad>(drawName(), adventureMap, j));
        }

        // Creating and spawning Viking objects

        for (int i = 0; i < numOfVikings; i++) {
            adventureMap.addHero(generateHeroes<Viking>(drawName(), adventureMap, j));
        }

        // Creating and spawning Knight objects

        for (int i = 0; i < numOfKnights; i++) {
            adventureMap.addHero(generateHeroes<Knight>(drawName(), adventureMap, j));
        }
    }

    // Creating and spawning Items

    for (int i = 0; i < numOfItems ;i++) {
        generateItem(adventureMap, itemsRange(mainEngine));
    }
}

void createMaps(std::vector<Map*> & mapsVector, int numOfMaps) {

    for(int it = 0; it < numOfMaps; it++){
        mapsVector.push_back( (Map*) new Map);

    }
}

bool isIntiger(std::string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}
