//
//  Created by
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
//#include <vector>
#include <random>
#include <fstream>
#include <string>

#include "Nomad.h"
#include "Knight.h"
#include "Slav.h"
#include "Viking.h"
#include "Map.h"

    void generateMap(Map & adventureMap){

        std::ifstream fNames("names.txt");
        std::random_device rd;
        std::mt19937 randomSeed(rd());

        int numOfObjLim = 400;

        while(numOfObjLim > 225) {
            std::cout << "Give me amount of objects to create:  ";
            //std::cin >> numOfObjLim;
            numOfObjLim = 10;
        }

        int numOfSlavs, numOfNomads, numOfKnights, numOfVikings;
        if(numOfObjLim >= 100) {
            std::uniform_int_distribution<int> slavsLimRange(1, 99);
            numOfSlavs = slavsLimRange(randomSeed);

            numOfNomads = (static_cast<int>((numOfObjLim - static_cast <float> (numOfSlavs))*(0.6)));
            if(numOfNomads > 75) numOfNomads = 75;

            numOfVikings = (static_cast<int>(((numOfObjLim - numOfNomads) - static_cast <float> (numOfSlavs))*(0.6)));
            if(numOfVikings > 62) numOfNomads = 62;

            numOfKnights = (numOfObjLim - numOfSlavs - (numOfNomads + numOfNomads/2));
            if(numOfKnights > 50) numOfKnights = 50;

            if(numOfNomads + numOfSlavs + numOfKnights < numOfObjLim) numOfSlavs += (numOfObjLim - (numOfNomads + numOfSlavs + numOfKnights));
        }
        else {
            std::uniform_int_distribution <int> slavsLimRange (1,numOfObjLim);
            numOfSlavs = slavsLimRange(randomSeed);
            numOfNomads = (static_cast <int> ((numOfObjLim - static_cast <float> (numOfSlavs))*(0.6) ));
            numOfVikings = (static_cast <int> (((numOfObjLim - numOfNomads) - static_cast <float> (numOfSlavs))*(0.6) ));
            numOfKnights = numOfObjLim - numOfSlavs - numOfNomads - numOfVikings;
        }

        std::cout << numOfSlavs << " ++ " << numOfNomads << " ++ " << numOfVikings << " ++ " <<  numOfKnights << "\n";

        if(fNames.good()) {
            std::string name;
            int tmpXPos, tmpYPos;

            /* Tworzenie i umieszczanie na mapie obiektów klasy Slav */

            for (int i = 0; i < numOfSlavs; i++) {
                fNames >> name;
                auto tmp = new Slav(name);
                do {
                    tmpXPos = Map::drawPos();
                    tmpYPos = Map::drawPos();
                } while(adventureMap.isFieldFull(tmpXPos, tmpYPos));
                tmp -> setCoords(tmpXPos,tmpYPos);
                adventureMap.spawn(tmp, tmpXPos, tmpYPos);
                std::cout << "Done " << i << " out of " << numOfSlavs << "\n";
            }
            std::cout << "\nDone " << numOfSlavs << " Slavs\n\n";
            /* Tworzenie i umieszczanie na mapie obiektów klasy Nomad */

            for (int i = 0; i < numOfNomads; i++) {
                fNames >> name;
                auto tmp = new Nomad(name);
                do {
                    tmpXPos = Map::drawPos();
                    tmpYPos = Map::drawPos();
                } while(adventureMap.isFieldFull(tmpXPos, tmpYPos));
                tmp -> setCoords(tmpXPos,tmpYPos);
                adventureMap.spawn(tmp, tmpXPos, tmpYPos);
                std::cout << "Done " << i << " out of " << numOfNomads << "\n";
            }
            std::cout << "\nDone " << numOfNomads << " Nomads\n\n";

            /* Tworzenie i umieszczanie na mapie obiektów klasy Knight */

            for (int i = 0; i < numOfKnights; i++) {
                fNames >> name;
                auto tmp = new Knight(name);
                do {
                    tmpXPos = Map::drawPos();
                    tmpYPos = Map::drawPos();
                } while(adventureMap.isFieldFull(tmpXPos, tmpYPos));
                tmp -> setCoords(tmpXPos,tmpYPos);
                adventureMap.spawn(tmp, tmpXPos, tmpYPos);
                std::cout << "Done " << i << " out of " << numOfKnights << "\n";
            }
            std::cout << "\nDone " << numOfKnights << " Knights\n\n";

            /* Tworzenie i umieszczanie na mapie obiektów klasy Viking */

            for (int i = 0; i < numOfVikings; i++) {
                fNames >> name;
                auto tmp = new Viking(name);
                do {
                    tmpXPos = Map::drawPos();
                    tmpYPos = Map::drawPos();
                } while(adventureMap.isFieldFull(tmpXPos, tmpYPos));
                tmp -> setCoords(tmpXPos,tmpYPos);
                adventureMap.spawn(tmp, tmpXPos, tmpYPos);
                std::cout << "Done " << i << " out of " << numOfVikings << "\n";
            }
            std::cout << "\nDone " << numOfVikings << " Vikings\n\n";
        }
        else {
            std::cout << "File \"names.txt\" not found" << std::endl;
        }
}

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

int main() {

    Map adventureMap;

    generateMap(adventureMap);

    adventureMap.show();

}