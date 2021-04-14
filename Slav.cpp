#include "Slav.h"

Slav::Slav() {
    name_ = "empty";
    attackDamage_ = 0;
    speed_ = 0;
    isAlive_ = true;
    posX_ = 0;
    posY_ = 0;

}

Slav::Slav(std::string name, int attackDamage, int speed, std::string weaponName, int weaponDamage, bool isBoothHanded, int weight) {
    name_=name;
    attackDamage_=attackDamage;
    speed_=speed;
    objWeapon_.fill(weaponName, weaponDamage, isBoothHanded, weight);
}

void Slav::show() {
    Being::show();
    objWeapon_.show();

}
