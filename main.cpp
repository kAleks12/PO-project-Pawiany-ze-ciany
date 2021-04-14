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
    /*
    std::vector < Being > istoty;

    int rozmiar=100;

    srand(time(nullptr));
    int los = (rand() % (2*rozmiar + 1)) - rozmiar;

    Being tablica_bytow[10];

    tablica_bytow[0].Show();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution <int> distance (1,10);
    std::cout << distance(mt) << std::endl;
    */

    Southern_Warrior pederasta("John", 10, 5, "excalibur", 100, false, 3, "jajoobcinacz", 90, false, 2);
    Knight frajer("Trajhardos", 10, 5, "lewa sluchawka", 9999, true, 3, "prawa sluchawka", 100000, 2);
    Slav aleks ("Debil", 10, 5, "Dildos", 1, true, 3);
    Field pytka;
    Being * tmp;


    tmp = &aleks;
    pytka.addBeing(tmp);
    tmp = &pederasta;
    pytka.addBeing(tmp);





    pytka.showField();

    //pederasta.show();
    //frajer.show();
    //aleks.show();

}
