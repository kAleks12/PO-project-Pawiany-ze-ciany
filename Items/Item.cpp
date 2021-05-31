//
// Created by Kacper Aleks on 21.04.2021.
//

#include "Item.h"

Item::Item(int itemId)
{
    switch(itemId){
        case 0:
            this -> isTemp_ = true;
            duration_ = -1;
            name_ = "health potion";
            healthBoost_ = 20;
            attackPoints_ = 0;
            speedBoost_ = 0;
            armorPoints_ = 0;

            break;
        case 1:
            isTemp_ = true;
            duration_ = 3;
            name_ = "strength potion";
            healthBoost_ = 0;
            attackPoints_ = 7;
            speedBoost_ = 0;
            armorPoints_ = 0;
            break;
        case 2:
            isTemp_ = true;
            duration_ = 3;
            name_ = "speed potion";
            healthBoost_ = 0;
            attackPoints_ = 0;
            speedBoost_ = 2;
            armorPoints_ = 0;
            break;
        case 3:
            name_ = "light armor";
            healthBoost_ = 0;
            attackPoints_ = 0;
            speedBoost_ = 0;
            armorPoints_ = 10;
            isTemp_ = false;
            break;
        case 4:
            name_ = "heavy armor";
            healthBoost_ = 0;
            attackPoints_ = 0;
            speedBoost_ = 0;
            armorPoints_ = 20;
            isTemp_ = false;
            break;
        case 5:
            name_ = "excalibur";
            healthBoost_ = 0;
            attackPoints_ = 50;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 6:
            name_ = "spear";
            healthBoost_ = 0;
            attackPoints_ = 27;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 7:
            name_ = "axe";
            healthBoost_ = 0;
            attackPoints_ = 14;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 8:
            name_ = "bulat";
            healthBoost_ = 0;
            attackPoints_ = 30;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 9:
            name_ = "two-handed sword";
            healthBoost_ = 0;
            attackPoints_ = 37;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
    }

}
Item::Item(const std::string & itemName){

    const std::map <std::string, int> namesId {
        {"hpotion",0} , {"stpotion", 1} , {"spotion", 2}, {"larmor",3}, {"harmor",4}, {"excalibur",5} , {"spear",6}, {"double axes",7}, {"bulat",8}, {"sword",9}
    };

    switch(namesId.at(itemName)){
        case 0:
            this -> isTemp_ = true;
            duration_ = -1;
            name_ = "health potion";
            healthBoost_ = 20;
            attackPoints_ = 0;
            speedBoost_ = 0;
            armorPoints_ = 0;

            break;
        case 1:
            isTemp_ = true;
            duration_ = 3;
            name_ = "strength potion";
            healthBoost_ = 0;
            attackPoints_ = 7;
            speedBoost_ = 0;
            armorPoints_ = 0;
            break;
        case 2:
            isTemp_ = true;
            duration_ = 3;
            name_ = "speed potion";
            healthBoost_ = 0;
            attackPoints_ = 0;
            speedBoost_ = 2;
            armorPoints_ = 0;
            break;
        case 3:
            name_ = "light armor";
            healthBoost_ = 0;
            attackPoints_ = 0;
            speedBoost_ = 0;
            armorPoints_ = 10;
            isTemp_ = false;
            break;
        case 4:
            name_ = "heavy armor";
            healthBoost_ = 0;
            attackPoints_ = 0;
            speedBoost_ = 0;
            armorPoints_ = 20;
            isTemp_ = false;
            break;
        case 5:
            name_ = "excalibur";
            healthBoost_ = 0;
            attackPoints_ = 50;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 6:
            name_ = "spear";
            healthBoost_ = 0;
            attackPoints_ = 27;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 7:
            name_ = "axe";
            healthBoost_ = 0;
            attackPoints_ = 14;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 8:
            name_ = "bulat";
            healthBoost_ = 0;
            attackPoints_ = 30;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
        case 9:
            name_ = "two-handed sword";
            healthBoost_ = 0;
            attackPoints_ = 37;
            speedBoost_ = 0;
            armorPoints_ = 0;
            isTemp_ = false;
            break;
    }

}

void Item::changeState() {
    if(isBeingUsed_)
        isBeingUsed_ = false;
    else
        isBeingUsed_ = true;
}

std::string Item::getName() {
    return name_;
}

void Item::show() {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    std::cout << "\nItem \"";
    std::cout << name_ << "\" :\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    if(healthBoost_ != 0) std::cout << "[*] health + " << healthBoost_ << ";\n";
    if(speedBoost_ != 0) std::cout << "[*] speed + " << speedBoost_ << ";\n";
    if(attackPoints_ != 0) std::cout << "[*] attack + " << attackPoints_ << ";\n";
    if(armorPoints_ != 0) std::cout << "[*] armor + " << armorPoints_ << ";\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    if(isBeingUsed_) {
        std::cout << "Is in use;\n";
        if(isTemp_) std::cout << "will be active for -> " << duration_ << ";\n";
    } else std::cout << "Is not in use;\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

}
void Item::destroy() {
    delete this;
}