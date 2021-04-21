//
// Created by Michał on 15.04.2021.
//

#include "Viking.h"

int Viking::numOfVikingsCreated_ = 0;

Viking::Viking() {
    Item axe1("axe"), axe2("axe");
    backpack_.push_back(axe1);
    backpack_.push_back(axe2);
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
}

Viking::Viking(std::string name) {

    std::random_device rd;
    std::mt19937 randomSeed(rd());

    name_ = name;
    speed_ = 2;

    std::uniform_int_distribution <int> strengthRange (17,20);
    strength_=strengthRange(randomSeed);


    Item axe1("axe"), axe2("axe"), lightArmor("larmor");

    backpack_.push_back(lightArmor);
    objArmor_ = "light armor";
    backpack_.push_back(axe1);
    objWeapon1_ =  "axe";
    backpack_.push_back(axe2);
    objWeapon2_ =  "axe";


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
}

void Viking::show() {
    std::cout << "\n\nObject is using -> " << objWeapon1_ << " and " << objWeapon2_ << " as weapons, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}
