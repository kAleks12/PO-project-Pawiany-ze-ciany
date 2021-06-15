//
// Created by Michał on 15.04.2021.
//

#include "Viking.h"

int Viking::numOfVikingsCreated_ = 0;//THE SAME DETAILS AS IN KNIGHT.CPP

Viking::Viking() {

    Item axes("double axes"), lightArmor("larmor");

    axes.changeState();
    lightArmor.changeState();

    backpack_.push_back(lightArmor);
    backpack_.push_back(axes);

    numOfVikingsCreated_++;
}
Viking::Viking(std::string name, int tribe, std::mt19937 & engine) {

    tribeId_ = tribe;
    name_ = std::move(name);
    speed_ = 2;

    std::uniform_int_distribution <int> strengthRange (17,20);
    strength_=strengthRange(engine);


    Item axes("double axes"), lightArmor("larmor");
    axes.changeState();
    lightArmor.changeState();

    backpack_.push_back(lightArmor);
    backpack_.push_back(axes);


    int numOfDigits = 0;
    int tmp = numOfVikingsCreated_;
    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }
    char tempTribeLetter;

    switch (tribeId_){

        case 0:
            strcpy(tribe_,"NORTH");
            break;

        case 1:
            strcpy(tribe_,"WEST");
            break;

        case 2:
            strcpy(tribe_,"EAST");
            break;

        case 3:
            strcpy(tribe_,"SOUTH");
            break;
    }

    if(numOfDigits == 0 || numOfDigits == 1){//creating ID
        id_[0] = tribe_[0];
        id_[1] = 'V';
        id_[2] = '0';
        id_[3] = numOfVikingsCreated_ + '0';
        id_[4] = '\0';
    }
    else{       //even for larger numbers of knights
        tmp = numOfVikingsCreated_;
        numOfDigits+=2;

        id_[numOfDigits] = '\0';
        while(numOfDigits > 1) {
            id_[--numOfDigits] = tmp % 10 + '0';
            tmp /= 10;
        }
        id_[1] = 'V';
        id_[0] = tribe_[0];
    }

    numOfVikingsCreated_++;

}
Viking::~Viking() {
    //std::cout << "Viking " << id_ << " has been slayed!"<< std::endl;
}

void Viking::show() {

    std::cout << "\n\nObject's weapons -> ";
    findItem(findWeapon()).show();
    std::cout << "\n\nObject's armor -> ";
    findItem(findArmor()).show();
    Being::show();

}
void Viking::destroy() {

    delete this;

}