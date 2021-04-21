#include "Knight.h"

int Knight::numOfKnightsCreated_ = 0;

Knight::Knight() {
    Item sword("sword");
    Item heavyArmor("harmor");

    backpack_.push_back(sword);
    objArmor_ = "sword";
    backpack_.push_back(heavyArmor);
    objWeapon_ =  "heavy armor";

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
}

Knight::Knight(std::string name){


    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 1;

    std::uniform_int_distribution <int> strengthRange (15,17);
    strength_=strengthRange(mt);

    Item sword("sword");
    Item heavyArmor("harmor");

    backpack_.push_back(sword);
    objWeapon_ = "sword";
    backpack_.push_back(heavyArmor);
    objArmor_ =  "heavy armor";

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
}

void Knight::changeStatus() {
    isOnHorse = !(isOnHorse);
}

void Knight::show() {
    std::cout << "\n\nObject is using -> " << objWeapon_ <<  " as weapon, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}

