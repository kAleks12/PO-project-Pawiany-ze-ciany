#include "Being.h"
#include <iostream>
#include <string.h>

Being::Being(): name_{"empty"}, strength_{0}, speed_{0}, posX_{0}, posY_{0}
{}

/*Being::Being(std::string name, int attackDamage, int speed): name_{name}, strength_{attackDamage}, speed_{speed}, posX_{0}, posY_{0}
{}*/

void Being::changeHp(int hpModifier){
    if((healthPoints_ + hpModifier <= 100) && (healthPoints_ + hpModifier >= 0))
    this -> healthPoints_ += hpModifier;
    else if(hpModifier > 0)
    healthPoints_ = 100;
    else
    healthPoints_ = 0;
}

std::string Being::getId() {
    std::string tmp = "----";
    tmp[0] = id_[0];
    tmp[1] = id_[1];
    tmp[2] = id_[2];
    tmp[3] = id_[3];
    return tmp;
}

void Being::setCoords(int xPos, int yPos) {
    this->posX_ = xPos;
    this->posY_ = yPos;
}

float Being::getTotalAttackPower() {
    float boosts;
    for(auto & tmp: backpack_) {
        if(tmp.attackBoost_ != 0) boosts += tmp.attackBoost_;
    }
    return (this -> strength_) + boosts;
}

void Being::show() {
    std::cout << "Hero's ID: " << id_[0] << id_[1] << id_[2] << id_[3] << " at position: " << posX_ << "," << posY_ << "\n";
    std::cout << "Hero's name: " << name_ << "\tHealth: " << healthPoints_ << "%\tAttack damage: " << strength_ << "\tSpeed: " << speed_ << std::endl;
    for(auto & tmp : backpack_){
        tmp.show();
    }
}

void Being::move(int posX, int posY) {
    setCoords(posX, posY);
}
