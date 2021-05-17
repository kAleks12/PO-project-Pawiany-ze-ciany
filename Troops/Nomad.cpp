#include <string>
#include "Nomad.h"

int Nomad::numOfNomadsCreated_ = 0;

Nomad::Nomad()
{
    Item bulat("bulat");
    Item lightArmor("larmor");
    backpack_.push_back(bulat);
    backpack_.push_back(lightArmor);


    numOfNomadsCreated_++;
}

Nomad::Nomad(std::string name, int tribe)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    tribe_ = tribe;
    name_ = name;
    speed_ = 2;

    std::uniform_int_distribution <int> strengthRange (12,15);
    strength_=strengthRange(mt);

    Item bulat("bulat");
    Item lightArmor("larmor");

    backpack_.push_back(lightArmor);
    objArmor_ = "light armor";
    backpack_.push_back(bulat);
    objWeapon_ =  "bulat";

    int numOfDigits = 0;
    int tmp = numOfNomadsCreated_;

    for(;tmp > 0;numOfDigits++){
        tmp /= 10;
    }

    if(numOfDigits == 0 || numOfDigits == 1){
        id_[0] = 'N';
        id_[1] = '0';
        id_[2] = numOfNomadsCreated_ + '0';
        id_[3] = name_[0];
    }
    else{
        tmp = numOfNomadsCreated_;
        numOfDigits+=2;

        id_[numOfDigits] = '\0';
        id_[--numOfDigits] = name_[0];
        while(numOfDigits>=1) {
            id_[--numOfDigits] = tmp % 10 + '0';
            tmp /= 10;
        }
        id_[0]= 'N';
    }

    numOfNomadsCreated_++;
}

void Nomad::show() {
    std::cout << "\n\nObject is using -> " << objWeapon_ << " as a weapon, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}

void Nomad::destroy() {
    delete this;
}

Nomad::~Nomad() {
    std::cout << "Nomad " << id_ << " has been slayed!"<< std::endl;
}