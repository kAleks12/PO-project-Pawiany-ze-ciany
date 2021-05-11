#include "Being.h"
#include <iostream>

Being::Being(): name_{"empty"}, id_{"init"}, strength_{0}
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
    std::string tmp;
    for(int i=0; id_[i] != '\0';i++) tmp[i] = id_[i];
    return id_;
}

float Being::getTotalAttackPower() {
    float boosts;
    for(auto & tmp: backpack_) {
        if(tmp.attackBoost_ != 0) boosts += tmp.attackBoost_;
    }
    return (this -> strength_) + boosts;
}

void Being::show() {
    std::cout << "Hero's ID: " << id_ << std::endl;
    std::cout << "Hero's name: " << name_ << "\tHealth: " << healthPoints_ << "%\tAttack damage: " << strength_ << std::endl;
    for(auto & tmp : backpack_){
        tmp.show();
    }
}

int Being::getTribe() const {
    return tribe_;
}

void Being::addItem(const Item & item) {
    backpack_.push_back(item);
}

bool Being::isAlive() {
    if(healthPoints_ > 0) return true;
    else return false;
}
