#include <string>
#include "Nomad.h"

int Nomad::numOfNomadsCreated_ = 0;

Nomad::Nomad()
{
    Item bulat("bulat");
    Item lightArmor("larmor");
    backpack_.push_back(bulat);
    backpack_.push_back(lightArmor);

    id_[0] = 'N';
    id_[1] = name_[0];
    if(numOfNomadsCreated_<10){
        id_[2] = '0';
        id_[3] = '0' + static_cast<char>(numOfNomadsCreated_);
    }
    else{
        id_[2] = '0' + static_cast<char>(numOfNomadsCreated_/10);
        id_[3] = '0' + static_cast<char>(numOfNomadsCreated_%10);
    }

    numOfNomadsCreated_++;
}

Nomad::Nomad(std::string name)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    name_ = name;
    speed_ = 3;

    std::uniform_int_distribution <int> strengthRange (12,15);
    strength_=strengthRange(mt);

    Item bulat("bulat");
    Item lightArmor("larmor");

    backpack_.push_back(lightArmor);
    objArmor_ = "light armor";
    backpack_.push_back(bulat);
    objWeapon_ =  "bulat";

    id_[0] = 'N';
    id_[1] = name_[0];
    if(numOfNomadsCreated_ < 10){
        id_[2] = '0';
        id_[3] = '0' + static_cast <char> (numOfNomadsCreated_);
    }
    else{
        id_[2] = '0' + static_cast <char> (numOfNomadsCreated_/10);
        id_[3] = '0' + static_cast <char> (numOfNomadsCreated_%10);
    }

    numOfNomadsCreated_++;
}

void Nomad::show() {
    std::cout << "\n\nObject is using -> " << objWeapon_ << " as a weapon, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}