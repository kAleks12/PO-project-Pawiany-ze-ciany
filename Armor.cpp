#include <iostream>
#include "Armor.h"

Armor::Armor(): name_{"empty"}, armorPoints_{0}, weight_{0}
{}

void Armor::show() {
    std::cout << "\nNazwa zbroi to: " << name_ << "\tpunkty pancerza wynosza: " << armorPoints_ << "\tciezar pancerza: " << weight_ <<  std::endl;
}
void Armor::fill(std::string armorName, int armorPoints, int weight) {
    name_ = armorName;
    armorPoints_ = armorPoints;
    weight_ = weight;
}