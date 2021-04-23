#include "Slav.h"

int Slav::numOfSlavsCreated_ = 0;


Slav::Slav() {

    Item spear("spear");
    Item lightArmor("larmor");

    backpack_.push_back(lightArmor);
    objArmor_ = "light armor";
    backpack_.push_back(spear);
    objWeapon_ =  "spear";

    int numOfDigits = 0;
    int tmp = numOfSlavsCreated_;
    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }
    if(numOfDigits == 0 || numOfDigits == 1){
        id_[0] = 'S';
        id_[1] = '0';
        id_[2] = numOfSlavsCreated_ + '0';
        id_[3] = name_[0];
    }
    else {
        tmp = numOfSlavsCreated_;
        for (int i = numOfDigits + 1; i >= 0; i--) {
            if (i == 0) id_[i] = 'S';
            else {
                if (i == numOfDigits + 1) id_[i] = name_[0];
                else {
                    id_[i] = tmp % 10 + '0';
                    tmp /= 10;
                }
            }
        }
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


    int numOfDigits = 0;
    int tmp = numOfSlavsCreated_;
    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }
    if(numOfDigits == 0 || numOfDigits == 1){
        id_[0] = 'S';
        id_[1] = '0';
        id_[2] = numOfSlavsCreated_ + '0';
        id_[3] = name_[0];
    }
    else {
        tmp = numOfSlavsCreated_;
        for (int i = numOfDigits + 1; i >= 0; i--) {
            if (i == 0) id_[i] = 'S';
            else {
                if (i == numOfDigits + 1) id_[i] = name_[0];
                else {
                    id_[i] = tmp % 10 + '0';
                    tmp /= 10;
                }
            }
        }
    }
    numOfSlavsCreated_++;
}

void Slav::show() {
    std::cout << "\n\nObject is using -> " << objWeapon_ << " as a weapon, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}
