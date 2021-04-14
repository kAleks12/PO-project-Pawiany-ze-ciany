//
//  Created by 
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
#include <ctime>
#include <vector>
#include "Being.h"
#include "SouthernWarrior.h"
#include "Knight.h"

int main() {
    std::vector < Being > istoty;
    int rozmiar=100;
    srand(time(nullptr));
    //int los = (rand()%(2*rozmiar+1))-rozmiar;

    SouthernWarrior pederasta("John", 10, 5, "excalibur", 100, false, 3, "jajoobcinacz", 90, false, 2);

    Knight frajer("Trajhardos", 10, 5, "lewa sluchawka", 9000, true, 3, "jajoobcinacz", 90, 2);

    pederasta.Show();

    frajer.Show();

    Being tablica_bytow[10];
    //tablica_bytow[0].Show();
}
