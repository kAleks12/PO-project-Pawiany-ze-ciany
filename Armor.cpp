#include <iostream>
#include "Armor.h"

Armor::Armor(): armorPoints_{0}, weight_{0}
{}

void Armor::show() {
    std::cout <<"\tArmor points: " << armorPoints_ << "\tArmor weight: " << weight_ <<  std::endl;
}
void Armor::fill(int armorPoints, int weight) {
    armorPoints_ = armorPoints;
    weight_ = weight;
}