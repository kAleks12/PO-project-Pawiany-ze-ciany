#include <string>
#include "Southern_Warrior.h"

Southern_Warrior::Southern_Warrior()
{
    name_ = "empty";
    attackDamage_ = 0;
    speed_ = 0;
    isAlive_ = true;
    posX_ = 0;
    posY_ = 0;
}
Southern_Warrior::Southern_Warrior(std::string name, int attackDamage, int speed, std::string weaponName, int weaponDamage, bool isBoothHanded, int weight, std::string weaponName2, int weaponDamage2, bool isBoothHanded2, int weight2){
    name_ = name;
    attackDamage_ = attackDamage;
    speed_ = speed;
    objWeapon_.fill(weaponName, weaponDamage, isBoothHanded, weight);
    objWeapon2_.fill(weaponName2, weaponDamage2, isBoothHanded2, weight2);
}

void Southern_Warrior::show() {
    Being::show();
    objWeapon_.show();
    objWeapon2_.show();
}