#include <iostream>
#include "Weapon.h"

Weapon::Weapon(): name_{"empty"}, attackPoints_{0}, weight_{0}
{}

void Weapon::show() {
     std::cout << "Weapon name: " << name_ << "\tWeapon's damage: " << attackPoints_ << "\tWeapons weight: " << weight_ << std::endl;
}

void Weapon::fill(std::string weaponName, int weaponDamage, int weight) {
    name_= weaponName;
    attackPoints_= weaponDamage;
    weight_= weight;
}
