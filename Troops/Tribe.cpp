#include "Tribe.h"

void Tribe::addSlav(const Slav & hero) {
    slavVector.push_back(hero);
}

void Tribe::addKnight(const Knight & hero) {
    knightVector.push_back(hero);
}

void Tribe::addNomad(const Nomad & hero) {
    nomadVector.push_back(hero);
}

void Tribe::addViking(const Viking & hero) {
    vikingVector.push_back(hero);
}

void Tribe::show() {

    std::cout << "Tribe content:\n";

    for(auto tmp : slavVector){
        std::cout << tmp.getId() << std::endl;
    }

    for(auto tmp : knightVector){
        std::cout << tmp.getId() << std::endl;
    }

    for(auto tmp : nomadVector){
        std::cout << tmp.getId() << std::endl;
    }

    for(auto tmp : vikingVector){
        std::cout << tmp.getId() << std::endl;
    }
    std::cout << std::endl;
}