//
// Created by Michał on 15.04.2021.
//

#include "Viking.h"

int Viking::numOfVikingsCreated_ = 0;
int Viking::moveCap_ =2 ;

Viking::Viking() {
    Item axe1("axe"), axe2("axe");
    backpack_.push_back(axe1);
    backpack_.push_back(axe2);

    numOfVikingsCreated_++;
}

Viking::Viking(std::string name, int tribe) {

    std::random_device rd;
    std::mt19937 randomSeed(rd());

    tribe_ = tribe;
    name_ = name;
    moveCap_ = 2;

    std::uniform_int_distribution <int> strengthRange (17,20);
    strength_=strengthRange(randomSeed);


    Item axe1("axe"), axe2("axe"), lightArmor("larmor");

    backpack_.push_back(lightArmor);
    objArmor_ = "light armor";
    backpack_.push_back(axe1);
    objWeapon1_ =  "axe";
    backpack_.push_back(axe2);
    objWeapon2_ =  "axe";


    int numOfDigits = 0;
    int tmp = numOfVikingsCreated_;
    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }
    if(numOfDigits == 0 || numOfDigits == 1){
        id_[0] = 'V';
        id_[1] = '0';
        id_[2] = numOfVikingsCreated_ + '0';
        id_[3] = name_[0];
    }
    else{
        tmp = numOfVikingsCreated_;
        numOfDigits+=2;

        id_[numOfDigits] = '\0';
        id_[--numOfDigits] = name_[0];
        while(numOfDigits>=1) {
            id_[--numOfDigits] = tmp % 10 + '0';
            tmp /= 10;
        }
        id_[0]= 'V';
    }

    numOfVikingsCreated_++;
}

void Viking::show() {
    std::cout << "\n\nObject is using -> " << objWeapon1_ << " and " << objWeapon2_ << " as weapons, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}
