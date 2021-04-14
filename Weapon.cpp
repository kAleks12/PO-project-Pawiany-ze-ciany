#include <iostream>
#include "Weapon.h"

Weapon::Weapon(): name_{"empty"}, damage_{0}, bothHanded_{false}, weight_{0}
{}

void Weapon::show() {
     std::cout << "Weapon name: " << name_ << "\tWeapon's damage: " << damage_ << "\tWeapons weight: " << weight_ << "\tIs it two-handed? " << bothHanded_ <<  std::endl;
}
void Weapon::fill(std::string weaponName, int weaponDamage, bool isBoothHanded, int weight) {
    name_= weaponName;
    damage_= weaponDamage;
    bothHanded_= isBoothHanded;
    weight_= weight;
}
