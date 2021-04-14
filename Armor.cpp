#include <iostream>
#include "Armor.h"

Armor::Armor(): name_{"empty"}, armorPoints_{0}, slowdown_{0}
{
}

void Armor::Show() {
    std::cout << "Nazwa zbroi to: " << name_ << " punkty pancerza wynosza: " << armorPoints_ << " ciezar pancerza: " << slowdown_ <<  std::endl;
}

void Armor::Fill(std::string armorName, int armorPoints, int weight) {
    name_=armorName;
    armorPoints_=armorPoints;
    slowdown_=weight;
}