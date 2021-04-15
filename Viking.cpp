//
// Created by Michał on 15.04.2021.
//

#include "Viking.h"

int Viking::numOfVikingsCreated_ = 0;
int Viking::numOfVikingsAlive_ = 0;

Viking::Viking() {

    name_ = "empty";
    strength_ = 0;
    speed_ = 0;
    isAlive_ = true;
    posX_ = 0;
    posY_ = 0;

    id_[0] = 'V';
    id_[1] = name_[0];
    if(numOfVikingsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfVikingsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfVikingsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfVikingsCreated_%10);
    }

    numOfVikingsCreated_++;
    numOfVikingsAlive_++;
}

Viking::Viking(std::string name) {

    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 2;

    std::uniform_int_distribution <int> strengthRange (17,20);
    strength_=strengthRange(mt);


    std::uniform_int_distribution <int> weaponDamageRange (20,23);
    objWeapon_.fill("Axe", weaponDamageRange(mt), false, 3);
    objArmor_.fill("Shield", 10, 2);

    id_[0] = 'V';
    id_[1] = name_[0];
    if(numOfVikingsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfVikingsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfVikingsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfVikingsCreated_%10);
    }

    numOfVikingsCreated_++;
    numOfVikingsAlive_++;

}

void Viking::show() {
    Being::show();
}
