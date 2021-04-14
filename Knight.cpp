#include "Knight.h"

Knight::Knight(){
    name_ = "empty";
    attackDamage_ = 0;
    speed_ = 0;
    isAlive_ = true;
    posX_ = 0;
    posY_ = 0;
}
Knight::Knight(std::string name, int attackDamage, int speed, std::string weaponName, int weaponDamage, bool isBoothHanded, int weight, std::string armorName, int armorPoints, int armorWeight){
    name_=name;
    attackDamage_=attackDamage;
    speed_=speed;
    objWeapon_.fill(weaponName, weaponDamage, isBoothHanded, weight);
    objArmor_.fill(armorName, armorPoints, armorWeight);
}

void Knight::show() {
    Being::show();
    objWeapon_.show();
    objArmor_.show();
}


