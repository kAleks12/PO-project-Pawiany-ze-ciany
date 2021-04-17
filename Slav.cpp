#include "Slav.h"

int Slav::numOfSlavsCreated_ = 0;
int Slav::numOfSlavsAlive_ = 0;

Slav::Slav() {

    id_[0] = 'S';
    id_[1] = name_[0];
    if(numOfSlavsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfSlavsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfSlavsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfSlavsCreated_%10);
    }

    numOfSlavsCreated_++;
    numOfSlavsAlive_++;
}

Slav::Slav(std::string name){

    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 3;

    std::uniform_int_distribution <int> strengthRange (10,12);
    strength_=strengthRange(mt);


    std::uniform_int_distribution <int> weaponDamageRange (10,12);
    objWeapon_.fill("spear", weaponDamageRange(mt), 3);

    id_[0] = 'S';
    id_[1] = name_[0];
    if(numOfSlavsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfSlavsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfSlavsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfSlavsCreated_%10);
    }

    numOfSlavsCreated_++;
    numOfSlavsAlive_++;
}

void Slav::show() {
    Being::show();
    objWeapon_.show();
}
