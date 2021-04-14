#include "Knight.h"

Knight::Knight(){
    name_ = "empty";
    attackDamage_ = 0;
    speed_ = 0;
    isAlive_ = true;
    posX_ = 0;
    posY_ = 0;
    hisWeapon_;
    hisArmor_;
}

void Knight::Show() {
    Being::Show();
    hisWeapon_.Show();
    hisArmor_.Show();
}

Knight::Knight(std::string name, int attackDamage, int speed, std::string weaponName, int weaponDamage, bool isBoothHanded, int weight, std::string armorName, int armorPoints, int armorWeight){
    name_=name;
    attackDamage_=attackDamage;
    speed_=speed;
    hisWeapon_.Fill(weaponName, weaponDamage, isBoothHanded, weight);
    hisArmor_.Fill(armorName, armorPoints, armorWeight);
}
