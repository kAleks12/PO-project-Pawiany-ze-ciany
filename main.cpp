//
//  Created by 
// Kacper Aleks
//     and
// Michał Malewicz
//
#include "Being.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <fstream>

int main() {
    //std::vector < Being > istoty;
    std::ofstream file ("wynik.txt") ;
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    for(int i=0; i<50;i++){
        file << dist(mt) << " ++ " ;
    }
    file << std::endl << "===============================================" << std::endl;
    for(int i=0; i<50;i++){
        file << (rand () % 10) + 1 << " ++ " ;
    }
    std::this_thread::sleep_for (std::chrono::milliseconds (500));



    /*Being beka("Thomas",10,10);
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
     */
}
