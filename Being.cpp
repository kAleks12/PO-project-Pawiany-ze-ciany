#include "Being.h"
#include <iostream>

Being::Being(): name_{"empty"}, strength_{0}, speed_{0}, posX_{0}, posY_{0}
{}
Being::Being(std::string name, int attackDamage, int speed/*, int startingPosX, int startingPosY*/): name_{name}, strength_{attackDamage}, speed_{speed}, posX_{0}, posY_{0}
{}

void Being::show() {
    std::cout << "\n\nHero's ID: " << id_[0] << id_[1] << id_[2] << id_[3] << std::endl;
    std::cout << "Hero's name: " << name_ << "\tHealth: " << healthPoints_ << "%\tAttack damage: " << strength_ << "\tSpeed: " << speed_ << std::endl;
    std::cout << "Hero's position: " << posX_ << "," << posY_ << "\n\n";
}

void Being::changeHp(int hpModifier){
    if((healthPoints_ + hpModifier <= 100) && (healthPoints_ + hpModifier >= 0))
    this -> healthPoints_ += hpModifier;
    else if(hpModifier > 0)
    healthPoints_ = 100;
    else
    healthPoints_ = 0;
}

std::string Being::getId() {
    return this->id_;
}
