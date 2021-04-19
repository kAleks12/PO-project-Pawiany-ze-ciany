#include "Knight.h"

int Knight::numOfKnightsCreated_ = 0;
int Knight::numOfKnightsAlive_ = 0;

Knight::Knight() {

    id_[0] = 'K';
    id_[1] = name_[0];
    if(numOfKnightsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfKnightsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfKnightsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfKnightsCreated_%10);
    }

    numOfKnightsCreated_++;
    numOfKnightsAlive_++;
}

Knight::Knight(std::string name){


    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 1;

    std::uniform_int_distribution <int> strengthRange (15,17);
    strength_=strengthRange(mt);

    std::uniform_int_distribution <int> weaponDamageRange (17,22);
    objWeapon_.fill("Two-handed sword", weaponDamageRange(mt), 5);
    objArmor_.fill(30, 20);

    id_[0] = 'K';
    id_[1] = name_[0];
    if(numOfKnightsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfKnightsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfKnightsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfKnightsCreated_%10);
    }

    numOfKnightsCreated_++;
    numOfKnightsAlive_++;
}

void Knight::show() {
    Being::show();
    objWeapon_.show();
    objArmor_.show();
}