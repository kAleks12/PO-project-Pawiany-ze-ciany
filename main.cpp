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

std::mt19937 mainEngine{std::random_device{}()};


//DRAWING FUNCTIONS
std::string drawName();
int drawInt(int, int);

//FUNCTIONS CATCHING ERRORS CONNECTED WITH INPUT PARAMETERS
bool isInteger(const std::string &);
bool isFloat(const std::string &);

//GENERATING HEROES AND ITEMS
template <typename ClassName> ClassName* generateHeroes(std::string , Map & , int );
void generateItem(Map & , int );

//CREATING MAPS AND FILLING THEM WITH HEROES AND ITEMS
void createMaps(std::vector <Map*> &, int);
void fillMap(Map & , int, float);







int main() {

    #ifdef SECOND_EXCEL_OUTPUT
    //LOOP FOR GETTING DATA FROM A NUMBER OF SIMULATIONS STARTED WITH DIFFERENT TROOPS RATIO
    for (float multiplier = 0.24; multiplier < 1; multiplier += 0.02) {
    #endif

        float tribesWins[4] = {0, 0, 0, 0};

        //VARIABLES
        std::vector<Map *> maps;

        std::string strAmountOfTroops = "1";
        std::string strTroopsMultiplier = "1";
        std::string strAmountOfMaps = "1";

        int amountOfTroops = 1;
        float troopsMultiplier = 1;
        int amountOfMaps = 1;


        //GETTING USER INPUT
        inputAmountMaps:

        #ifdef SECOND_EXCEL_OUTPUT
        amountOfMaps = 100;
        amountOfTroops = 200;
        troopsMultiplier = multiplier;
        #endif

        #ifdef SCREEN_OUTPUT
        std::cout << "How many maps should there be?\n";
        std::cin>>strAmountOfMaps;

        if (isInteger(strAmountOfMaps) && (amountOfMaps > 0))
            amountOfMaps = stoi(strAmountOfMaps);
        else {
            std::cout << "invalid number\n";
            goto inputAmountMaps;
        }

        inputAmountTroops:

        std::cout << "How many troops in each tribe should there be?\n";
        std::cin>>strAmountOfTroops;

        if (isInteger(strAmountOfTroops)) {
            amountOfTroops = stoi(strAmountOfTroops);
            if ((amountOfTroops > Map::getMapSize() / 2) || (amountOfTroops <= 0)) {
                std::cout << "number is to high or low\n";
                goto inputAmountTroops;
            }
        } else {
            std::cout << "invalid number\n";
            goto inputAmountTroops;
        }

        inputTroopsMultiplier:

        std::cout << "What part of whole tribe should the troops' main type be? (float number)\n";
        std::cin >> strTroopsMultiplier;

            if (isFloat(strTroopsMultiplier)) {
            troopsMultiplier = stof(strTroopsMultiplier);
            if ((troopsMultiplier > 0.97) || (troopsMultiplier < 0.5)) {
                std::cout << "number is to high or low\n";
                goto inputTroopsMultiplier;
            }
        } else {
            std::cout << "invalid number\n";
            goto inputTroopsMultiplier;
        }
        #endif

        system("cls");



        //CREATING MAPS AND FILLING THEM

        createMaps(maps, amountOfMaps);

        for (auto & map: maps) {
            fillMap(*map, amountOfTroops, troopsMultiplier);
        }

        //RUNNING SIMULATION
        int mapNumber = 0;
        while (!maps.empty()) {
            for (auto & map: maps) {
                if (map->numOfTribes() > 1) {

                    #ifdef SCREEN_OUTPUT
                    Map::goToXY(0, 0);
                    Map::clearScreen(0,81);
                    Map::goToXY(0, 0);
                    std::cout << "Iteration of map no: " << mapNumber % maps.size() << std::endl;
                    #endif

                    map->iteration();
                    //system("pause");

                } else {

                    #ifdef SECOND_EXCEL_OUTPUT
                    for (int tribe : tribesWins) {
                        if (map->isTribeAlive(tribe))
                            tribesWins[tribe]++;
                    }
                    #endif

                    #ifdef SCREEN_OUTPUT
                    system("cls");
                    #endif

                    map->generateSummary(amountOfTroops, troopsMultiplier);
                    map->deactivate();

                    //DELETING FINISHED MAPS FROM THE VECTOR
                    for (auto it = maps.begin(); it != maps.end();) {
                        if ((*it)->getStatus()) {
                            it = maps.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }
                mapNumber++;

            }
        }

        #ifdef SECOND_EXCEL_OUTPUT
        std::ofstream researchFile("ExcelOutput.txt", std::ios::out | std::ios::app);
        researchFile << "\n" << troopsMultiplier;
        for (float tribe : tribesWins) {
            researchFile << " ; " << tribe / (float)amountOfMaps;
        }
        std::cout << "\nSimulation with " << multiplier * 100 << "% of main units is over" << std::endl;
    }
        #endif

    #ifndef SECOND_EXCEL_OUTPUT
    std::cout << "END OF THE SIMULATION"<<std::endl;
    #endif

}










int drawInt(int min, int max) {  //generating random position on the map
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

bool isInteger(const std::string & str) {
    for(char i : str)
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

void createMaps(std::vector<Map*> & mapsVector, int numOfMaps) {

    for(int it = 0; it < numOfMaps; it++){
        mapsVector.push_back( (Map*) new Map);
    }
}

template <typename ClassName> ClassName* generateHeroes(std::string name, Map & map, int tribe){   //spawning new heroes
    int tmpXPos, tmpYPos;

    auto tmp = new ClassName(name, tribe, mainEngine);
    do {
        tmpXPos = drawInt(0, (sqrt(Map::getMapSize()) - 1));
        tmpYPos = drawInt(0, (sqrt(Map::getMapSize()) - 1));
    } while (map.isFieldFull(tmpXPos, tmpYPos));

    map.spawn(tmp, tmpXPos, tmpYPos);

    return tmp;
}

void generateItem(Map & map, int itemId)    //spawning items on the map
{
    int tmpX, tmpY;
    do {
        tmpX = drawInt(0, (sqrt(Map::getMapSize()) - 1));
        tmpY = drawInt(0, (sqrt(Map::getMapSize()) - 1));
    } while(map.isFieldFull(tmpX, tmpY));

    map.addItem(tmpX, tmpY, itemId);
}

void fillMap(Map & adventureMap, int amountOfTroops, float multiplier){   //filling map

    int numOfSlavs = 0;
    int numOfNomads = 0;
    int numOfKnights = 0;
    int numOfVikings = 0;

    for(int tribeId =0; tribeId < 4; tribeId++) {  //each tribe

        if( tribeId == 0){
            numOfVikings = multiplier * amountOfTroops;
            numOfNomads = ((1-multiplier)/3) * amountOfTroops;
            numOfKnights = ((1-multiplier)/3) * amountOfTroops;
            numOfSlavs = ((1-multiplier)/3) * amountOfTroops;
        }
        if( tribeId == 1){
            numOfKnights = multiplier * amountOfTroops;
            numOfNomads = ((1-multiplier)/3) * amountOfTroops;
            numOfSlavs = ((1-multiplier)/3) * amountOfTroops;
            numOfVikings = ((1-multiplier)/3) * amountOfTroops;
        }
        if( tribeId == 2){
            numOfSlavs = multiplier * amountOfTroops;
            numOfNomads = ((1-multiplier)/3) * amountOfTroops;
            numOfKnights = ((1-multiplier)/3) * amountOfTroops;
            numOfVikings = ((1-multiplier)/3) * amountOfTroops;
        }
        if( tribeId == 3){
            numOfNomads = multiplier * amountOfTroops;
            numOfSlavs = ((1-multiplier)/3) * amountOfTroops;
            numOfKnights = ((1-multiplier)/3) * amountOfTroops;
            numOfVikings = ((1-multiplier)/3) * amountOfTroops;
        }

        //ADJUSTING NUMBER OF TROOPS WITHIN TRIBE IF UNDER THE LIMIT

        while(numOfNomads + numOfSlavs + numOfKnights + numOfVikings < amountOfTroops){
            switch(tribeId){
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
        //ADJUSTING NUMBER OF TROOPS WITHIN TRIBE IF ABOVE THE LIMIT

        while(numOfNomads + numOfSlavs + numOfKnights + numOfVikings > amountOfTroops){
            switch(tribeId){
                case 0:
                    numOfSlavs--;
                    break;
                case 1:
                    numOfNomads--;
                    break;
                case 2:
                    numOfKnights--;
                    break;
                case 3:
                    numOfVikings--;
                    break;
            }
        }


        //Creating and spawning Slav objects

        for (int i = 0; i < numOfSlavs; i++) {
            adventureMap.addToList(generateHeroes<Slav>(drawName(), adventureMap, tribeId));
        }

        // Creating and spawning Nomad objects

        for (int i = 0; i < numOfNomads; i++) {
            adventureMap.addToList(generateHeroes<Nomad>(drawName(), adventureMap, tribeId));
        }

        // Creating and spawning Viking objects

        for (int i = 0; i < numOfVikings; i++) {
            adventureMap.addToList(generateHeroes<Viking>(drawName(), adventureMap, tribeId));
        }

        // Creating and spawning Knight objects

        for (int i = 0; i < numOfKnights; i++) {
            adventureMap.addToList(generateHeroes<Knight>(drawName(), adventureMap, tribeId));
        }
    }

    // Creating and spawning Items
    std::uniform_int_distribution <int> itemsRange(1, 9);

#ifndef SECOND_EXCEL_OUTPUT
    int amountOfItems = drawInt(0, 100);
#endif

#ifdef SECOND_EXCEL_OUTPUT
    int amountOfItems = 40;
#endif

    for (int i = 0; i < amountOfItems ;i++) {
        generateItem(adventureMap, itemsRange(mainEngine));
    }
}