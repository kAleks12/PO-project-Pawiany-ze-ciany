#include "Being.h"
#include <iostream>

Being::Being()
{
    name_ = "empty";
    id_[0] = 'i';
    id_[1] = 'n';
    id_[2] = 'i';
    id_[3] = 't';
    strength_ = 0;
}
Being::~Being() = default;

void Being::changeHp(int hpModifier){

    if((healthPoints_ + hpModifier < 100))
        healthPoints_ += hpModifier;
    else healthPoints_ = 100;

}
void Being::addItem(const Item & item) {

    try {
        backpack_.push_back(item);
    }
    catch( const std::bad_alloc & badAlloc) {
        std::cout << "Program crashed in Field::addItem :)";
        exit(69);
    }

}
void Being::changeWeapon() {

    for(auto & item: backpack_) {
        if(!item.isTemp_){
            if(item.attackPoints_ > findItem(findWeapon()).attackPoints_ ){
                item.changeState();
                deactivateItem(findWeapon());
            }
            if(item.armorPoints_ > findItem(findArmor()).armorPoints_){
                item.changeState();
                deactivateItem(findArmor());
            }
        }
    }

}
void Being::useTempItems() {

    int potLim =0;
    int pos = 0;

    for(auto & item: backpack_) {
            if (item.isTemp_) {
                if (item.isBeingUsed_) {
                    if (item.duration_ > 0)
                        item.duration_--;
                    else {
                        backpack_.erase(backpack_.begin() + pos);
                    }
                }
                if (!item.isBeingUsed_ && potLim == 0) {
                    if (item.duration_ > 0) {
                        item.duration_--;
                        item.changeState();
                    } else {
                        if (item.duration_ == -1)
                            changeHp(item.healthBoost_);
                        backpack_.erase(backpack_.begin() + pos);
                    }
                    potLim++;
                }
            }
            pos++;


    }

}
void Being::deactivateItem(const std::string& itemName) {

    for(auto & item: backpack_)
        if(item.getName() == itemName)
            item.changeState();

}

std::string Being::getId() {

    return id_;

}
int Being::getHP() {

    return healthPoints_;

}
int Being::getTotalAP() {

    int boosts = 0;

    for(auto & item: backpack_) {
        if(item.attackPoints_ != 0 && item.isBeingUsed_ && !item.isTemp_)
            boosts += item.attackPoints_;
        if(item.isTemp_ && item.isBeingUsed_ && item.duration_ >= 0)
            boosts += item.attackPoints_;
    }

    return strength_ + boosts;

}
int Being::getDefense() {

    int boosts = 0;

    for(auto & item: backpack_) {
        if(item.armorPoints_ != 0 && item.isBeingUsed_ && !item.isTemp_)
            boosts += item.armorPoints_;
        if(item.isTemp_ && item.isBeingUsed_ && item.duration_ >= 0)
            boosts += item.armorPoints_;
    }
    return boosts/2;

}
int Being::getTribe() const {

    return tribe_;

}
int Being::getSpeed() const {

    int boosts;

    for(auto & item: backpack_) {
        if(item.isTemp_ && item.isBeingUsed_ && item.duration_ >= 0)
            boosts += item.speedBoost_;
    }
    return speed_;

}

Item Being::findItem(const std::string& itemName) {

    for(auto & item: backpack_)
        if(item.getName() == itemName)
            return item;
    return backpack_.front();

}

std::string Being::findArmor() {

    for(auto & item: backpack_) {
        if(item.armorPoints_ > 0 && item.isBeingUsed_ && !item.isTemp_)
            return item.getName();
    }
    return "not found";

}
std::string Being::findWeapon() {

    for(auto & item: backpack_) {
        if(item.attackPoints_ > 0 && item.isBeingUsed_ && !item.isTemp_)
            return item.getName();
    }
    return "not found";

}
std::string Being::findPotion(std::string name) {

    for(auto & item: backpack_) {
        if(item.isTemp_ && item.getName() == name)
            return name;
    }
    return "not found";

}

void Being::printBackpack() {

    for(auto & item:backpack_)
        item.show();

}
void Being::show() {

    std::cout << "Hero " << name_ << "\n\thp: " << healthPoints_ << "\tstrength: " << strength_ << "\t id: " << id_ << std::endl;

}

bool Being::isAlive() {

    if(healthPoints_ > 0)
        return true;
    else
        return false;

}
bool Being::whetherPickUp(const Item & item) {

    if(item.isTemp_ && (findPotion(item.name_) == "health potion" ||  findPotion(item.name_) == "not found"))
        return true;
    else{
        if(item.isTemp_)
            return false;
        else{
            if (item.attackPoints_ > 0) {
                if (item.attackPoints_ > findItem(findWeapon()).attackPoints_)
                    return true;
                else return false;
            } else {
                if (item.armorPoints_ > findItem(findArmor()).armorPoints_)
                    return true;
                else return false;
            }
        }
    }

}