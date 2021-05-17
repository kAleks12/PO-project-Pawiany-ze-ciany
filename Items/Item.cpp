//
// Created by Kacper Aleks on 21.04.2021.
//

#include "Item.h"

Item::Item(int itemId)
{
    switch(itemId){
        case 0:
            this -> isTemp_ = true;
            this -> duration_ = -1;
            this -> name_ = "health potion";
            this -> healthBoost_ = 20;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;

            break;
        case 1:
            this -> isTemp_ = true;
            this -> duration_ = 3;
            this -> name_ = "strength potion";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 7;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            break;
        case 2:
            this -> isTemp_ = true;
            this -> duration_ = 3;
            this -> name_ = "speed potion";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 2;
            this -> armorBoost_ = 0;
            break;
        case 3:
            this -> name_ = "light armor";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 10;
            this -> isTemp_ = false;
            break;
        case 4:
            this -> name_ = "heavy armor";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 20;
            this -> isTemp_ = false;
            break;
        case 5:
            this -> name_ = "excalibur";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 50;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            this -> isTemp_ = false;
            break;
        case 6:
            this -> name_ = "spear";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 27;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            this -> isTemp_ = false;
            break;
        case 7:
            this -> name_ = "axe";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 14;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            this -> isTemp_ = false;
            break;
        case 8:
            this -> name_ = "bulat";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 30;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            this -> isTemp_ = false;
            break;
        case 9:
            this -> name_ = "two-handed sword";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 37;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            this -> isTemp_ = false;
            break;
    }
}
Item::Item(const std::string & itemName){
    const std::map <std::string, int> namesId {{"hpotion",0} , {"stpotion", 1} , {"spotion", 2}, {"larmor",3}, {"harmor",4}, {"excalibur",5} , {"spear",6}, {"double axes",7}, {"bulat",8}, {"sword",9}};
    switch(namesId.at(itemName))  {
        case 0:
            this -> isTemp_ = true;
            this -> duration_ = -1;
            this -> name_ = "health potion";
            this -> healthBoost_ = 20;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;

            break;
        case 1:
            this -> isTemp_ = true;
            this -> duration_ = 3;
            this -> name_ = "strength potion";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 7;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            break;
        case 2:
            this -> isTemp_ = true;
            this -> duration_ = 3;
            this -> name_ = "speed potion";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 2;
            this -> armorBoost_ = 0;
            break;
        case 3:
            this -> isTemp_ = false;
            this -> name_ = "light armor";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 10;
            break;
        case 4:
            this -> isTemp_ = false;
            this -> name_ = "heavy armor";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 0;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 20;
            break;
        case 5:
            this -> isTemp_ = false;
            this -> name_ = "excalibur";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 50;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            break;
        case 6:
            this -> isTemp_ = false;
            this -> name_ = "spear";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 27;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            break;
        case 7:
            this -> isTemp_ = false;
            this -> name_ = "axe";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 14;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            break;
        case 8:
            this -> isTemp_ = false;
            this -> name_ = "bulat";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 30;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            break;
        case 9:
            this -> isTemp_ = false;
            this -> name_ = "two-handed sword";
            this -> healthBoost_ = 0;
            this -> attackBoost_ = 37;
            this -> speedBoost_ = 0;
            this -> armorBoost_ = 0;
            break;
    }
}

void Item::show() {
    std::cout << "Item \"";
    std::cout << name_ << "\" :\n";
    if(healthBoost_ != 0) std::cout << "[*] health + " << healthBoost_ << ";\n";
    if(speedBoost_ != 0) std::cout << "[*] speed + " << speedBoost_ << ";\n";
    if(attackBoost_ != 0) std::cout << "[*] attack + " << attackBoost_ << ";\n";
    if(armorBoost_ != 0) std::cout << "[*] armor + " << armorBoost_ << ";\n";
    if(isBeingUsed_) {
        std::cout << "Is in use "  ";\n";
        if(isTemp_) std::cout << "will be active for -> " << duration_ << ";\n";
    } else std::cout << "Is not in use;\n";
}

void Item::changeState() {
    if(isBeingUsed_)
        isBeingUsed_ = false;
    else
        isBeingUsed_ = true;
}

void Item::destroy() {
    delete this;
}
