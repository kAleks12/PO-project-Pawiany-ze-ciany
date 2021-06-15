#include <string>
#include <utility>
#include "Nomad.h"

int Nomad::numOfNomadsCreated_ = 0;//THE SAME DETAILS AS IN KNIGHT.CPP

Nomad::Nomad()
{
    Item bulat("bulat");
    bulat.changeState();

    Item lightArmor("larmor");
    lightArmor.changeState();

    backpack_.push_back(bulat);
    backpack_.push_back(lightArmor);


    numOfNomadsCreated_++;
}
Nomad::Nomad(std::string name, int tribe, std::mt19937 & engine)
{

    tribeId_ = tribe;
    name_ = std::move(name);
    speed_ = 2;

    std::uniform_int_distribution <int> strengthRange (12,15);
    strength_=strengthRange(engine);

    Item bulat("bulat");
    bulat.changeState();

    Item lightArmor("larmor");
    lightArmor.changeState();

    backpack_.push_back(lightArmor);
    backpack_.push_back(bulat);


    int numOfDigits = 0;
    int tmp = numOfNomadsCreated_;

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
        id_[1] = 'N';
        id_[2] = '0';
        id_[3] = numOfNomadsCreated_ + '0';
        id_[4] = '\0';
    }
    else{       //even for larger numbers of knights
        tmp = numOfNomadsCreated_;
        numOfDigits+=2;

        id_[numOfDigits] = '\0';
        while(numOfDigits > 1) {
            id_[--numOfDigits] = tmp % 10 + '0';
            tmp /= 10;
        }
        id_[1] = 'N';
        id_[0] = tribe_[0];
    }

    numOfNomadsCreated_++;

}
Nomad::~Nomad() {
    //std::cout << "Nomad " << id_ << " has been slayed!"<< std::endl;
}

void Nomad::show() {

    std::cout << "\n\nObject's weapons -> ";
    findItem(findWeapon()).show();
    std::cout << "\n\nObject's armor -> ";
    findItem(findArmor()).show();
    Being::show();
    Being::show();

}
void Nomad::destroy() {

    delete this;

}