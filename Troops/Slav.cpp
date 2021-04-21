#include "Slav.h"

int Slav::numOfSlavsCreated_ = 0;


Slav::Slav() {

    Item spear("spear");
    Item lightArmor("larmor");

    backpack_.push_back(lightArmor);
    objArmor_ = "light armor";
    backpack_.push_back(spear);
    objWeapon_ =  "spear";

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
}

Slav::Slav(std::string name){

    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 3;

    std::uniform_int_distribution <int> strengthRange (10,12);
    strength_=strengthRange(mt);


    Item spear("spear");
    Item lightArmor("larmor");

    backpack_.push_back(lightArmor);
    objArmor_ = "light armor";
    backpack_.push_back(spear);
    objWeapon_ = "spear";


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
}

void Slav::show() {
    std::cout << "\n\nObject is using -> " << objWeapon_ << " as a weapon, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}
