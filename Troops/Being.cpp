#include "Being.h"
#include <iostream>

Being::Being(): name_{"empty"}, id_{"init"}, strength_{0}
{}
Being::~Being() = default;

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
    int boosts;
    for(auto & item: backpack_) {
        if(item.attackBoost_ != 0 && item.isBeingUsed_) boosts += item.attackBoost_;
    }
    return this -> strength_ + boosts;
}
int Being::getDefense() {
    int boosts;
    for(auto & item: backpack_) {
        if(item.armorBoost_ != 0 && item.isBeingUsed_) boosts += item.armorBoost_;
    }
    return this -> strength_ + boosts;
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

Item& Being::findArmor() {
    for(auto & item: backpack_) {
        if(item.armorBoost_ > 0 && item.isBeingUsed_ && !item.isTemp_)  return item;
    }
}
Item& Being::findWeapon() {
    for(auto & item: backpack_) {
        if(item.attackBoost_ > 0 && item.isBeingUsed_ && !item.isTemp_)  return item;
    }
}

void Being::useEq() {
    Item currWeapon = findWeapon();
    Item currArmor = findArmor();
    int potLim =0;
    for(auto & item: backpack_) {
        if(item.attackBoost_ > currWeapon.attackBoost_ && !item.isTemp_){
            item.changeState();
            currWeapon.changeState();
        }
        if(item.armorBoost_ > currArmor.armorBoost_ && !item.isTemp_){
            item.changeState();
            currArmor.changeState();
        }
        if(item.isTemp_){
            if(!item.isBeingUsed_ && potLim == 0){
                if(item.duration_ > 0) {
                    item.duration_--;
                    item.changeState();
                }
                else {
                    changeHp(item.healthBoost_);
                    item.destroy();
                }
                potLim++;
            }
            if(item.isBeingUsed_){
                if(item.duration_ > 0)
                    item.duration_ --;
                else item.destroy();
            }
        }
    }
}

int Being::getHp() {
    return healthPoints_;
}
