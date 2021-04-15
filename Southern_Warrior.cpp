#include <string>
#include "Southern_Warrior.h"

int Southern_Warrior::numOfWarriorsCreated_ = 0;
int Southern_Warrior::numOfWarriorAlive_ = 0;

Southern_Warrior::Southern_Warrior()
{
    name_ = "empty";
    strength_ = 0;
    speed_ = 0;
    isAlive_ = true;
    posX_ = 0;
    posY_ = 0;

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

Southern_Warrior::Southern_Warrior(std::string name){

    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 3;

    std::uniform_int_distribution <int> strengthRange (12,15);
    strength_=strengthRange(mt);


    std::uniform_int_distribution <int> weaponDamageRange (10,15);//nie nice
    objWeapon_.fill("Bulat", weaponDamageRange(mt), false, 4);
    objWeapon2_.fill("Bulat", weaponDamageRange(mt), false, 4);

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

void Southern_Warrior::show() {
    Being::show();
    objWeapon_.show();
    objWeapon2_.show();
}