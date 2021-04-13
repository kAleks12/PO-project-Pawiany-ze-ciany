//
// Created by Kacper Aleks on 12.04.2021.
//

#include "Being.h"
#include <iostream>

Being::Being(std::string name, int attackDamage, int speed): healthPoints_{100}, name_{name}, attackDamage_{attackDamage}, speed_{speed}
{}
void Being::Show() {
    std::cout << "Name of the object: " << name_ << "\tHealth: " << healthPoints_ << "\tAttack damage: " << attackDamage_ << "\tSpeed: " << speed_ << std::endl;
}