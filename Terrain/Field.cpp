#include <iostream>
#include "Field.h"

Field::Field() {
    heroesAtThisField_[0] = nullptr;
    heroesAtThisField_[1] = nullptr;
}

void Field::addBeing( Being * hero) {
    if((hero != nullptr) && isSpace()){
        if(heroesAtThisField_[0]== nullptr)
            heroesAtThisField_[0] = hero;
        else{
            heroesAtThisField_[1] = hero;
        }
    }
}

void Field::removeBeing(int position) {
    heroesAtThisField_[position] = nullptr;
}

Being * Field::getHero(int pos) {

    return heroesAtThisField_[pos];
}

bool Field::isPosEmpty(int pos) {
    return (heroesAtThisField_[pos] == nullptr);
}

bool Field::isSpace() {
    return !((heroesAtThisField_[0] != nullptr) && (heroesAtThisField_[1] != nullptr));
}

void Field::showField() {
    if((isPosEmpty(0))&&(isPosEmpty(1)))
        std::cout << "Pole jest puste" << std::endl;
    else {
        std::cout << "Zawartosc pola: \n\n";
        if (heroesAtThisField_[0] != nullptr) {
            std::cout << "Hero 1 \n";
            (heroesAtThisField_[0])->show();
        }
        if (heroesAtThisField_[1] != nullptr) {
            std::cout << "Hero 2: \n";
            (heroesAtThisField_[1])->show();
        }
    }
}
