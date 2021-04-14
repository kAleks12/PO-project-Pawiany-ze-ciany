#include <iostream>
#include "Field.h"

Field::Field() {

    whatContains_[0] = nullptr;
    whatContains_[1] = nullptr;
    isEmpty_ = true;
}

void Field::addBeing( Being * hero) {
    if((hero != nullptr) && isEmpty_){
        if(whatContains_[0]== nullptr)
            whatContains_[0] = hero;
        else{
            whatContains_[1] = hero;
            isEmpty_ = false;
        }



    }

}

void Field::removeBeing(int position) {
    isEmpty_ = true;
    whatContains_[position] = nullptr;

}

void Field::showField() {

    if(isEmpty_)
    std::cout << "Pole jest puste" << std::endl;
    else {
        std::cout << "Zawartosc pola: \n\n";
        if (whatContains_[0] != nullptr) {
            std::cout << "Hero 1 \n";
            (whatContains_[0])->show();
        }
        if (whatContains_[1] != nullptr) {
            std::cout << "Hero 2: \n";
            (whatContains_[1])->show();
        }
    }
}

bool Field::isEmpty() {
    return isEmpty_;

}
