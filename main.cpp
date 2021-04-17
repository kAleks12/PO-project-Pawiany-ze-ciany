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

/*
int attack(int armor, int weapon) {
    int damage = (weapon - armor)/5;
    if(damage>100)
        damage=100;
}
*/

int main() {
    std::ifstream fNames("names.txt");
    /*
    std::vector < Being > beings;

    int size=100;

    srand(time(nullptr));
    int los = (rand() % (2*size + 1)) - size;

    Being beings [10];

    beings[0].Show();

    Nomad pederasta("John", 10, 5, "excalibur", 100, false, 3, "jajoobcinacz", 90, false, 2);

    Knight frajer("Trajhardos", 10, 5, "lewa sluchawka", 9999, true, 3, "prawa sluchawka", 100000, 2);

    Slav aleks ("Debil", 10, 5, "Dildos", 1, true, 3);
    Field pytka;
    Being * tmp;
    tmp = &aleks;
    pytka.addBeing(tmp);
    tmp = &pederasta;
    pytka.addBeing(tmp);

    //pytka.showField();

    pederasta.show();
    frajer.show();
    aleks.show();*/

    std::random_device rd;
    std::mt19937 randomSeed(rd());

    Map adventureMap;
    int numOfObjLim = 400;

    while(numOfObjLim > 225) {
        std::cout << "Give me amount of objects to create:  ";
        std::cin >> numOfObjLim;
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
                tmpXPos = adventureMap.drawPos();
                tmpYPos = adventureMap.drawPos();
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
                tmpXPos = adventureMap.drawPos();
                tmpYPos = adventureMap.drawPos();
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
                tmpXPos = adventureMap.drawPos();
                tmpYPos = adventureMap.drawPos();
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
                tmpXPos = adventureMap.drawPos();
                tmpYPos = adventureMap.drawPos();
            } while(adventureMap.isFieldFull(tmpXPos, tmpYPos));
            tmp -> setCoords(tmpXPos,tmpYPos);
            adventureMap.spawn(tmp, tmpXPos, tmpYPos);
            std::cout << "Done " << i << " out of " << numOfVikings << "\n";
        }
        std::cout << "\nDone " << numOfVikings << " Vikings\n\n";
    }
    else {
        std::cout << "File \"names.txt\" not found" << std::endl;
        return 69;
    }
    adventureMap.show();
}