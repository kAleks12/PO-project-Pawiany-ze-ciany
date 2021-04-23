#include <string>
#include "Nomad.h"

int Nomad::numOfNomadsCreated_ = 0;

Nomad::Nomad()
{
    Item bulat("bulat");
    Item lightArmor("larmor");
    backpack_.push_back(bulat);
    backpack_.push_back(lightArmor);

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
    else {
        tmp = numOfNomadsCreated_;
        for (int i = numOfDigits + 1; i >= 0; i--) {
            if (i == 0) id_[i] = 'N';
            else {
                if (i == numOfDigits + 1) id_[i] = name_[0];
                else {
                    id_[i] = tmp % 10 + '0';
                    tmp /= 10;
                }
            }
        }
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
    else {
        tmp = numOfNomadsCreated_;
        for (int i = numOfDigits + 1; i >= 0; i--) {
            if (i == 0) id_[i] = 'N';
            else {
                if (i == numOfDigits + 1) id_[i] = name_[0];
                else {
                    id_[i] = tmp % 10 + '0';
                    tmp /= 10;
                }
            }
        }
    }
    numOfNomadsCreated_++;
}

void Nomad::show() {
    std::cout << "\n\nObject is using -> " << objWeapon_ << " as a weapon, and wears -> " << objArmor_ << "\n" ;
    Being::show();
}