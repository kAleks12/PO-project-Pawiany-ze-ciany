//
//  Created by
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
//#include <ctime>
//#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <stdio.h>

#include "Being.h"
#include "Southern_Warrior.h"
#include "Knight.h"
#include "Slav.h"
#include "Map.h"
#include "Field.h"

/*
int attack(int armor, int weapon) {
    int damage = (weapon - armor)/5;
    if(damage>100)
        damage=100;
}
*/

int main() {
    std::fstream fNames;
    fNames.open( "names.txt", std::fstream::in );
    /*
    std::vector < Being > beings;

    int size=100;

    srand(time(nullptr));
    int los = (rand() % (2*size + 1)) - size;

    Being beings [10];

    beings[0].Show();

    Southern_Warrior pederasta("John", 10, 5, "excalibur", 100, false, 3, "jajoobcinacz", 90, false, 2);

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
    std::mt19937 mt(rd());
    std::uniform_int_distribution <int> slavLimRange (0,99);

    Map adventureMap;

    int numOfObjLim;

    std::cout << "Give me amount of objects to create " << std::endl;
    //std::cin >> numOfObjLim;
    numOfObjLim = 1;

    int slavLim = slavLimRange(mt);
    slavLim = 5;


    if(fNames.good()) {
        std::string name;
        fNames >> name;
        std::cout << fNames.is_open() << std::endl;

        for (int i = 0; i < slavLim; i++) {
            //fNames >> name;
            std::cout << name << std::endl;
            Slav * tmp = new Slav();
        }

        for (int i = 0; i < numOfObjLim; i++) {
            //adventureMap.spawn();
        }

    }
    else{
        std::cout << "Plik nie zostal znaleziony" << std::endl;
        return 0;
    }









}
