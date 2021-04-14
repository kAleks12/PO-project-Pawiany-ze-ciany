#include "Being.h"
#include <iostream>

Being::Being(): name_{"empty"}, attackDamage_{0}, speed_{0}, isAlive_{true}, posX_{0}, posY_{0}
{}
Being::Being(std::string name, int attackDamage, int speed/*, int startingPosX, int startingPosY*/): name_{name}, attackDamage_{attackDamage}, speed_{speed}, isAlive_{true}, posX_{0}, posY_{0}
{}

void Being::show() {
    std::cout << "Name of the object: " << name_ << "\tHealth: " << healthPoints_ << "\tAttack damage: " << attackDamage_ << "\tSpeed: " << speed_ << std::endl;
    std::cout << "position of the object: " << posX_<<","<<posY_<<" , is object alive? "<<isAlive_<<std::endl;
}
void Being::changeHp(int hpModifier){
    if((healthPoints_ + hpModifier <= 100) && (healthPoints_ + hpModifier >= 0))
    this -> healthPoints_ += hpModifier;
    else if(hpModifier > 0)
    healthPoints_ = 100;
    else
    healthPoints_ = 0;
}