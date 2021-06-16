#include "Knight.h"

#include <utility>

int Knight::numOfKnightsCreated_ = 0;

Knight::Knight() {  //default constructor

    //CREATING STARTING ITEMS
    Item sword("sword");
    sword.changeState();

    Item heavyArmor("harmor");
    heavyArmor.changeState();

    backpack_.push_back(sword);
    backpack_.push_back(heavyArmor);

    numOfKnightsCreated_++;
}
Knight::Knight(std::string name, int tribe, std::mt19937 & engine){     //CONSTRUCTOR WITH SPECIFIED NAME, TRIBEid AND WITH PROVIDED RANDOM ENGINE USED TO DRAW HERO STRENGTH

    //INITIALIZING ATTRIBUTES
    name_ = std::move(name);
    tribeId_ = tribe;
    speed_ = 1;

    std::uniform_int_distribution <int> strengthRange (15,18);
    strength_=strengthRange(engine);


    //CREATING STARTING ITEMS
    Item sword("sword");
    sword.changeState();

    Item heavyArmor("harmor");
    heavyArmor.changeState();

    backpack_.push_back(sword);
    backpack_.push_back(heavyArmor);

    //CREATING ID
    int numOfDigits = 0;
    int tmp = numOfKnightsCreated_;

    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }


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
        id_[1] = 'K';
        id_[2] = '0';
        id_[3] = numOfKnightsCreated_ + '0';
        id_[4] = '\0';
    }
    else{       //even for larger numbers of knights
        tmp = numOfKnightsCreated_;
        numOfDigits+=2;

        id_[numOfDigits] = '\0';
        while(numOfDigits > 1) {
            id_[--numOfDigits] = tmp % 10 + '0';
            tmp /= 10;
        }
        id_[1] = 'K';
        id_[0] = tribe_[0];
    }

    numOfKnightsCreated_++;

}
Knight::~Knight() {
    //std::cout << "Knight " << id_ << " is officially dead  !" << std::endl;
}

void Knight::show() {//printing hero details

    std::cout << "\n\nObject's weapons -> ";
    findItem(findWeapon()).show();
    std::cout << "\n\nObject's armor -> ";
    findItem(findArmor()).show();
    Being::show();

}
void Knight::destroy() {//MUERTA MUAHAHAHA
    delete this;
}
