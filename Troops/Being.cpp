#include "Being.h"
#include <iostream>

Being::Being(): name_{"empty"}, id_{"init"}, strength_{0}
{}
Being::~Being()
{}

void Being::changeHp(int hpModifier){
    if((healthPoints_ + hpModifier < 100)) this -> healthPoints_ += hpModifier;
    else healthPoints_ = 100;
}

void Being::addItem(const Item & item) {
    backpack_.push_back(item);
}

std::string Being::getId() {
    return id_;
}

int Being::getTotalAttackPower() {
    float boosts;
    for(auto & tmp: backpack_) {
        if(tmp.attackBoost_ != 0) boosts += tmp.attackBoost_;
    }
    return (this -> strength_) + boosts;
}

int Being::getTribe() const {
    return tribe_;
}

int Being::getSpeed() const {
    return speed_;
}

bool Being::isAlive() {
    if(healthPoints_ > 0) return true;
    else return false;
}

void Being::show() {
    std::cout << "Hero " << name_ << "\n\thp: " << healthPoints_ << "\tstrength: " << strength_ << "\t id: " << id_ << std::endl;
}