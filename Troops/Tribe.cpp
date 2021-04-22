#include "Tribe.h"

void Tribe::addSlav(Slav hero) {
    slavVector.push_back(hero);
    slavQuantity++;
}

void Tribe::addKnight(Knight hero) {
    knightVector.push_back(hero);
    knightQuantity++;
}

void Tribe::addNomad(Nomad hero) {
    nomadVector.push_back(hero);
    nomadQuantity++;
}

void Tribe::addViking(Viking hero) {
    vikingVector.push_back(hero);
    vikingQuantity++;
}

void Tribe::show() {

    std::cout << "Tribe content:\n";

    for(int i=0;i<slavVector.size();i++){
        Slav tmp = slavVector[i];
        std::cout << tmp.getId() << std::endl;
    }

    for(int i=0;i<knightVector.size();i++){
        Knight tmp = knightVector[i];
        std::cout << tmp.getId() << std::endl;
    }

    for(int i=0;i<nomadVector.size();i++){
        Nomad tmp = nomadVector[i];
        std::cout << tmp.getId() << std::endl;
    }

    for(int i=0;i<vikingVector.size();i++){
        Viking tmp = vikingVector[i];
        std::cout << tmp.getId() << std::endl;
    }
    std::cout << std::endl;
}
