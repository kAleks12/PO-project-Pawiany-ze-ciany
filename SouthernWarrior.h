#ifndef MAP_H_SOUTHERNWARRIOR_H
#define MAP_H_SOUTHERNWARRIOR_H


#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class SouthernWarrior:public Being{
private:
    Weapon hisWeapon_;
    Weapon hisWeapon2_;
public:
    SouthernWarrior();
    SouthernWarrior(std::string, int, int, std::string, int, bool, int, std::string, int, bool, int);
    void Show();
};


#endif //MAP_H_SOUTHERNWARRIOR_H
