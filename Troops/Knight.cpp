#include "Knight.h"

int Knight::numOfKnightsCreated_ = 0;

Knight::Knight() {
    Item sword("sword");
    Item heavyArmor("harmor");

    backpack_.push_back(sword);
    objArmor_ = "sword";
    backpack_.push_back(heavyArmor);
    objWeapon_ =  "heavy armor";

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
    else {
        tmp = numOfKnightsCreated_;
        for (int i = numOfDigits + 1; i >= 0; i--) {
            if (i == 0) id_[i] = 'K';
            else {
                if (i == numOfDigits + 1) id_[i] = name_[0];
                else {
                    id_[i] = tmp % 10 + '0';
                    tmp /= 10;
                }
            }
        }
    }
    numOfKnightsCreated_++;
}

Knight::Knight(std::string name){
    name_ = name;
    speed_ = 1;

    strength_= 15;

    Item sword("sword");
    Item heavyArmor("harmor");

    backpack_.push_back(sword);
    objWeapon_ = "sword";
    backpack_.push_back(heavyArmor);
    objArmor_ =  "heavy armor";

    int numOfDigits = 0;
    int tmp = numOfKnightsCreated_;
    char nameTmp[81];

    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }
    if(numOfDigits == 0 || numOfDigits == 1){
        id_[0] = 'K';
        id_[1] = '0';
        id_[2] = numOfKnightsCreated_ + '0';
        id_[3] = name_[0];
    }
    else {
        tmp = numOfKnightsCreated_;
        for (int i = numOfDigits + 1; i >= 0; i--) {
            if (i == 0) id_[i] = 'K';
            else {
                if (i == numOfDigits + 1) id_[i] = name_[0];
                else {
                    id_[i] = tmp % 10 + '0';
                    tmp /= 10;
                }
            }
        }
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

