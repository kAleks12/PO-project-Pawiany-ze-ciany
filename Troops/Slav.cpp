#include "Slav.h"

#include <utility>

int Slav::numOfSlavsCreated_ = 0;//THE SAME DETAILS AS IN KNIGHT.CPP


Slav::Slav() {

    Item spear("spear");
    Item lightArmor("larmor");

    spear.changeState();
    lightArmor.changeState();

    backpack_.push_back(lightArmor);
    backpack_.push_back(spear);


    numOfSlavsCreated_++;

}
Slav::Slav(std::string name, int tribe, std::mt19937 & engine){


    tribe_ = tribe;
    name_ = std::move(name);
    speed_ = 3;

    std::uniform_int_distribution <int> strengthRange (10,12);
    strength_=strengthRange(engine);


    Item spear("spear");
    Item lightArmor("larmor");

    spear.changeState();
    lightArmor.changeState();

    backpack_.push_back(lightArmor);
    backpack_.push_back(spear);


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
        id_[4] = '\0';
    }
    else{
        tmp = numOfSlavsCreated_;
        numOfDigits+=2;

        id_[numOfDigits] = '\0';
        id_[--numOfDigits] = name_[0];
        while(numOfDigits>=1) {
            id_[--numOfDigits] = tmp % 10 + '0';
            tmp /= 10;
        }
        id_[0]= 'S';
    }

    numOfSlavsCreated_++;

}
Slav::~Slav() {

    //std::cout << "Slav " << id_ << " has been slayed!"<< std::endl;

}


void Slav::show() {

    std::cout << "\n\nObject's weapons -> ";
    findItem(findWeapon()).show();
    std::cout << "\n\nObject's armor -> ";
    findItem(findArmor()).show();
    Being::show();

}
void Slav::destroy() {

    delete this;

}