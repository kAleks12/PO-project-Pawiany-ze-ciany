#include "Being.h"
#include <iostream>


Being::Being()//default being
{
    name_ = "empty";
    id_[0] = 'i';
    id_[1] = 'n';
    id_[2] = 'i';
    id_[3] = 't';
    strength_ = 0;
}
Being::~Being() = default;

void Being::changeHp(int hpMod){    //modifying amount of heroes HP points

    if((healthPoints_ + hpMod < 100))
        healthPoints_ += hpMod;
    else healthPoints_ = 100;

}
void Being::addKill() {
    killCounter_++;
}
void Being::addItem(const Item & item) {    //adding items to heroes backpack

    backpack_.push_back(item);

}
void Being::useTmpItems() {//using temporary items (potions)

    int potLim =0;
    int pos = 0;

    for(auto & item: backpack_) {
        if (item.isTmp_) {
            if (item.isBeingUsed_) {
                if (item.duration_ > 0)
                    item.duration_--;//items are being used
                else {
                    backpack_.erase(backpack_.begin() + pos);//items are being deleted
                }
            }
            if (!item.isBeingUsed_ && potLim == 0) {//drinking new potions
                if (item.duration_ > 0) {
                    item.duration_--;
                    item.changeState();
                } else {
                    if (item.duration_ == -1)//one time use potions
                        changeHp(item.healthBoost_);
                    backpack_.erase(backpack_.begin() + pos);
                }
                potLim++;
            }
        }
        pos++;


    }

}
void Being::updateWeapon() {    //finding and choosing the best weapon in heroes backpack

    for(auto & item: backpack_) {
        if(!item.isTmp_){
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
void Being::deactivateItem(const std::string& itemName) {//deactivating items

    for(auto & item: backpack_)
        if(item.getName() == itemName)
            item.changeState();

}

std::string Being::getId() {

    return id_;

}
std::string Being::getName() {
    return name_;
}
int Being::getHP() {

    return healthPoints_;

}
int Being::getTotalAP() {//summing every potion, weapon and base attack points

    int boosts = 0;

    for(auto & item: backpack_) {
        if(item.attackPoints_ != 0 && item.isBeingUsed_ && !item.isTmp_)
            boosts += item.attackPoints_;
        if(item.isTmp_ && item.isBeingUsed_ && item.duration_ >= 0)
            boosts += item.attackPoints_;
    }

    return strength_ + boosts;

}
int Being::getDefense() {//summing every potion and armor

    int boosts = 0;

    for(auto & item: backpack_) {
        if(item.armorPoints_ != 0 && item.isBeingUsed_ && !item.isTmp_)
            boosts += item.armorPoints_;
        if(item.isTmp_ && item.isBeingUsed_ && item.duration_ >= 0)
            boosts += item.armorPoints_;
    }
    return boosts/2;

}
int Being::getTribe() const {

    return tribe_;

}
int Being::getSpeed() const {//summing every potion and basic speed

    int boosts = 0;

    for(auto & item: backpack_) {
        if(item.isTmp_ && item.isBeingUsed_ && item.duration_ >= 0)
            boosts += item.speedBoost_;
    }
    return speed_;

}
int Being::getKills() {
    return killCounter_;
}

Item Being::findItem(const std::string& itemName) {//returning certain item

    for(auto & item: backpack_)
        if(item.getName() == itemName)
            return item;
    return backpack_.front();

}

std::string Being::findArmor() {//returning armor name

    for(auto & item: backpack_) {
        if(item.armorPoints_ > 0 && item.isBeingUsed_ && !item.isTmp_)
            return item.getName();
    }
    return "not found";

}
std::string Being::findWeapon() {//returning weapon name

    for(auto & item: backpack_) {
        if(item.attackPoints_ > 0 && item.isBeingUsed_ && !item.isTmp_)
            return item.getName();
    }
    return "not found";

}
std::string Being::findPotion(std::string name) {//confirming whether there is an certain potion *could have been bool function EGHM*

    for(auto & item: backpack_) {
        if(item.isTmp_ && item.getName() == name)
            return name;
    }
    return "not found";

}

void Being::printBackpack() {//printing backpacks content

    for(auto & item:backpack_)
        item.show();

}
void Being::show() {//printing heroes details

    std::cout << "Hero " << name_ << "\n\thp: " << healthPoints_ << "\tstrength: " << strength_ << "\t id: " << id_ << std::endl;

}

bool Being::isAlive() {//u good bro?

    if(healthPoints_ > 0)
        return true;
    else
        return false;

}
bool Being::whetherPickUp(const Item & item) {//does hero wants to pick up an item

    if(item.isTmp_ && (findPotion(item.name_) == "health potion" || findPotion(item.name_) == "not found"))
        return true;
    else{
        if(item.isTmp_)
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