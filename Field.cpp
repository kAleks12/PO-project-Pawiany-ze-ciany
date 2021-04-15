#include <iostream>
#include "Field.h"

Field::Field() {

    heroesAtThisField_[0] = nullptr;
    heroesAtThisField_[1] = nullptr;
    isEmpty_ = true;
}

void Field::addBeing( Being * hero) {
    if((hero != nullptr) && isEmpty_){
        if(heroesAtThisField_[0]== nullptr)
            heroesAtThisField_[0] = hero;
        else{
            heroesAtThisField_[1] = hero;
            isEmpty_ = false;
        }
    }

}

void Field::removeBeing(int position) {
    isEmpty_ = true;
    heroesAtThisField_[position] = nullptr;
}

void Field::showField() {

    if(isEmpty_)
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

bool Field::isEmpty() {return isEmpty_;}
