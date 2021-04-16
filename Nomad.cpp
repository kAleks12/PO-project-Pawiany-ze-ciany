#include <string>
#include "Nomad.h"

int Nomad::numOfWarriorsCreated_ = 0;
int Nomad::numOfWarriorAlive_ = 0;

Nomad::Nomad()
{

    id_[0] = 'N';
    id_[1] = name_[0];
    if(numOfWarriorsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfWarriorsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfWarriorsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfWarriorsCreated_%10);
    }

    numOfWarriorsCreated_++;
    numOfWarriorAlive_++;
}

Nomad::Nomad(std::string name){

    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 3;

    std::uniform_int_distribution <int> strengthRange (12,15);
    strength_=strengthRange(mt);


    std::uniform_int_distribution <int> weaponDamageRange (10,15);//nie nice
    objWeapon_.fill("Bulat", weaponDamageRange(mt), 4);
    objWeapon2_.fill("Bulat", weaponDamageRange(mt), 4);

    id_[0] = 'N';
    id_[1] = name_[0];
    if(numOfWarriorsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfWarriorsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfWarriorsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfWarriorsCreated_%10);
    }

    numOfWarriorsCreated_++;
    numOfWarriorAlive_++;
}

void Nomad::show() {
    Being::show();
    objWeapon_.show();
    objWeapon2_.show();
}