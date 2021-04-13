//
//  Created by 
// Kacper Aleks
//     and
// Michał Malewicz
//

#include <iostream>
#include <windows.h>
#include <time.h>
#include <vector>
#include "Being.h"

int main() {
    std::vector < Being > istoty;
    int rozmiar=100;
    srand(time(NULL));
    int los = (rand()%(2*rozmiar+1))-rozmiar;
    for(int i=0;i<10;i++)
    {
        los = (rand()%(2*rozmiar+1))-rozmiar;
        std::cout<<los<<std::endl;
    }
    Being beka("Thomas",10,10);
    Being baka("Sheep",5,5);
    beka.Show();
    baka.Show();
    baka.ChangeHp(-6);
    baka.Show();
    baka.ChangeHp(10);
    baka.Show();

    Being tablica_bytow[10];

    tablica_bytow[0].Show();

    system("Pause");
}
