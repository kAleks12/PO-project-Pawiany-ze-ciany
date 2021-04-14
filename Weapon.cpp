#include <iostream>
#include "Weapon.h"

Weapon::Weapon(): name_{"empty"}, damage_{0}, bothHanded_{false}, slowdown_{0}
{
}

void Weapon::Show() {
     std::cout << "Nazwa broni to: " << name_ << " damage broni to " << damage_ << " ciezar broni to: " << slowdown_ << " czy bron jest dworeczna? " << bothHanded_ <<  std::endl;
}

void Weapon::Fill(std::string weaponName, int weaponDamage, bool isBoothHanded, int weight) {
    name_=weaponName;
    damage_=weaponDamage;
    bothHanded_=isBoothHanded;
    slowdown_=weight;
}
