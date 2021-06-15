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


//DRAWING FUNCTIONS
std::string drawName();
int drawPos(int, int);

//GENERATING HEROES AND ITEMS
template <typename ClassName> ClassName* generateHeroes(std::string , Map & , int );
void generateItem(Map & , int );

//CREATING MAPS AND FILLING THEM WITH HEROES AND ITEMS
void createMaps(std::vector <Map*> &, int);
void fillMap(Map & , int, float);

//FUNCTIONS CATCHING ERRORS CONNECTED WITH INPUT PARAMETERS
bool isInteger(const std::string &);
bool isFloat(const std::string &);

std::mt19937 mainEngine{std::random_device{}()};








int main() {

    //VARIABLES
    std::vector <Map*> maps;

    std::string strAmountOfTroops = "1";
    std::string strTroopsMultiplier = "1";
    std::string strAmountOfMaps = "1";

    int amountOfTroops = 1;
    float troopsMultiplier = 1;
    int amountOfMaps = 1;


    //GETTING USER INPUT
    inputAmountMaps:

    std::cout<<"How many maps should there be?\n";
    std::cin>>strAmountOfMaps;

    if(isInteger(strAmountOfMaps) && (amountOfMaps > 0))
        amountOfMaps = stoi(strAmountOfMaps);
    else{
        std::cout<<"invalid number\n";
        goto inputAmountMaps;
    }

    inputAmountTroops:

    std::cout<<"How many troops in each tribe should there be?\n";
    std::cin>>strAmountOfTroops;

    if(isInteger(strAmountOfTroops)) {
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

    inputTroopsMultiplier:

    std::cout<<"What percentage of whole tribe should the troops' main type be?\n";
    std::cin>>strTroopsMultiplier;

    if(isFloat(strTroopsMultiplier)) {
        troopsMultiplier = stof(strTroopsMultiplier);
        if ((troopsMultiplier > 0.97) || (troopsMultiplier < 0.5) ){
            std::cout<<"number is to high or low\n";
            goto inputTroopsMultiplier;
        }
    }
    else{
        std::cout<<"invalid number\n";
        goto inputTroopsMultiplier;
    }

    system("cls");



    //CREATING MAPS AND FILLING THEM

    createMaps(maps, amountOfMaps);

    for(auto & map: maps){
        fillMap(*map, amountOfTroops, troopsMultiplier);
    }


    //RUNNING SIMULATION
    int i = 0;
    while(!maps.empty()){
        for(auto & map: maps){
            if(map -> numOfTribes() > 1){

#ifdef USER_OUTPUT
                Map::goToXY(0, 0);
                Map::clearScreen(0,81);
                Map::goToXY(0, 0);
                std::cout << "Iteration of map no: " << i % maps.size() << std::endl;
#endif

                map->iteration();
                //system("pause");
            }
            else{
#ifdef USER_OUTPUT
                Map::goToXY(0, 0);
                Map::clearScreen(0,81);
                Map::goToXY(0, 0);
#endif
                map->generateSummary(amountOfTroops, troopsMultiplier);
                map->deactivate();
                //system("pause");
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










int drawPos(int min, int max) {  //generating random position on the map
    std::uniform_int_distribution<int> posRange(min, max);
    int randomNum;

    randomNum = posRange(mainEngine);
    return randomNum;
}

std::string drawName(){  //generating names

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
        tmpXPos = drawPos(0, (sqrt(Map::getMapSize())-1));
        tmpYPos = drawPos(0, (sqrt(Map::getMapSize())-1));
    } while (map.isFieldFull(tmpXPos, tmpYPos));

    map.spawn(tmp, tmpXPos, tmpYPos);

    return tmp;
}

void generateItem(Map & map, int itemId)    //spawning items on the map
{
    int tmpX, tmpY;
    do {
        tmpX = drawPos(0, (sqrt(Map::getMapSize())-1));
        tmpY = drawPos(0, (sqrt(Map::getMapSize())-1));
    } while(map.isFieldFull(tmpX, tmpY));

    map.addItem(tmpX, tmpY, itemId);
}


void fillMap(Map & adventureMap, int amountOfTroops, float multiplier){   //filling map

    int numOfSlavs = 0;
    int numOfNomads = 0;
    int numOfKnights = 0;
    int numOfVikings = 0;

    for(int j=0;j<4;j++) {  //each tribe

        if( j == 0){
            numOfVikings = multiplier * amountOfTroops;
            numOfNomads = ((1-multiplier)/3) * amountOfTroops;
            numOfKnights = numOfNomads;
            numOfSlavs = numOfNomads;
        }
        if( j == 1){
            numOfKnights = multiplier * amountOfTroops;
            numOfNomads = ((1-multiplier)/3) * amountOfTroops;
            numOfSlavs = numOfNomads;
            numOfVikings = numOfNomads;
        }
        if( j == 2){
            numOfSlavs = multiplier * amountOfTroops;
            numOfNomads = ((1-multiplier)/3) * amountOfTroops;
            numOfKnights = numOfNomads;
            numOfVikings = numOfNomads;
        }
        if( j == 3){
            numOfNomads = multiplier * amountOfTroops;
            numOfSlavs = ((1-multiplier)/3) * amountOfTroops;
            numOfKnights = numOfSlavs;
            numOfVikings = numOfSlavs;
        }

        while(numOfNomads + numOfSlavs + numOfKnights + numOfVikings < amountOfTroops){
            switch(j){
                case 0:
                    numOfSlavs++;
                    break;
                case 1:
                    numOfNomads++;
                    break;
                case 2:
                    numOfKnights++;
                    break;
                case 3:
                    numOfVikings++;
                    break;
            }
        }


        //Creating and spawning Slav objects

        for (int i = 0; i < numOfSlavs; i++) {
            adventureMap.addToList(generateHeroes<Slav>(drawName(), adventureMap, j));
        }

        // Creating and spawning Nomad objects

        for (int i = 0; i < numOfNomads; i++) {
            adventureMap.addToList(generateHeroes<Nomad>(drawName(), adventureMap, j));
        }

        // Creating and spawning Viking objects

        for (int i = 0; i < numOfVikings; i++) {
            adventureMap.addToList(generateHeroes<Viking>(drawName(), adventureMap, j));
        }

        // Creating and spawning Knight objects

        for (int i = 0; i < numOfKnights; i++) {
            adventureMap.addToList(generateHeroes<Knight>(drawName(), adventureMap, j));
        }
    }

    // Creating and spawning Items

    std::uniform_int_distribution <int> itemsRange(1, 9);
    int amountOfItems = drawPos(0, 100);

    for (int i = 0; i < amountOfItems ;i++) {
        generateItem(adventureMap, itemsRange(mainEngine));
    }
}

void createMaps(std::vector<Map*> & mapsVector, int numOfMaps) {

    for(int it = 0; it < numOfMaps; it++){
        mapsVector.push_back( (Map*) new Map);

    }
}

bool isInteger(const std::string & str) {
    for (char i : str)
        if (isdigit(i) == false)
            return false;
    return true;
}
bool isFloat(const std::string & str){
    for (char i : str)
        if (isdigit(i) == false && i != '.')
            return false;
    return true;
}