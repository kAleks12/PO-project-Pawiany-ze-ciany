#include <string>
#include "SouthernWarrior.h"

SouthernWarrior::SouthernWarrior()
{
    name_ = "empty";
    attackDamage_ = 0;
    speed_ = 0;
    isAlive_ = true;
    posX_ = 0;
    posY_ = 0;
    hisWeapon_;
    hisWeapon2_;
}

void SouthernWarrior::Show() {
    Being::Show();
    hisWeapon_.Show();
    hisWeapon2_.Show();

}

SouthernWarrior::SouthernWarrior(std::string name, int attackDamage, int speed, std::string weaponName, int weaponDamage, bool isBoothHanded, int weight, std::string weaponName2, int weaponDamage2, bool isBoothHanded2, int weight2){
    name_=name;
    attackDamage_=attackDamage;
    speed_=speed;
    hisWeapon_.Fill(weaponName, weaponDamage, isBoothHanded, weight);
    hisWeapon2_.Fill(weaponName2, weaponDamage2, isBoothHanded2, weight2);
}
