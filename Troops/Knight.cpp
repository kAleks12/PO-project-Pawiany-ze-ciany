#include "Knight.h"

int Knight::numOfKnightsCreated_ = 0;

Knight::Knight() {
    Item sword("sword");
    Item heavyArmor("harmor");

    backpack_.push_back(sword);
    objArmor_ = "sword";
    backpack_.push_back(heavyArmor);
    objWeapon_ =  "heavy armor";

    numOfKnightsCreated_++;
}

Knight::Knight(std::string name, int tribe){
    name_ = name;
    tribe_ = tribe;
    strength_= 15;
    speed_ = 1;

    Item sword("sword");
    Item heavyArmor("harmor");

    backpack_.push_back(sword);
    objWeapon_ = "sword";
    backpack_.push_back(heavyArmor);
    objArmor_ =  "heavy armor";

    int numOfDigits = 0;
    int tmp = numOfKnightsCreated_;

    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }
    if(numOfDigits == 0 || numOfDigits == 1){
        id_[0] = 'K';
        id_[1] = '0';
        id_[2] = numOfKnightsCreated_ + '0';
        id_[3] = name_[0];
    }
    else{
        tmp = numOfKnightsCreated_;
        numOfDigits+=2;

        id_[numOfDigits] = '\0';
        id_[--numOfDigits] = name_[0];
        while(numOfDigits>=1) {
            id_[--numOfDigits] = tmp % 10 + '0';
            tmp /= 10;
        }
        id_[0]= 'K';
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

void Knight::destroy() {
    delete this;
}

Knight::~Knight() {
    std::cout << "Knight " << id_ << " has been slayed!" << std::endl;
}