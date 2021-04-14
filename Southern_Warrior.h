#ifndef MAP_H_SOUTHERN_WARRIOR_H
#define MAP_H_SOUTHERN_WARRIOR_H


#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class Southern_Warrior: public Being{
private:
    Weapon objWeapon_;
    Weapon objWeapon2_;
public:
    Southern_Warrior();
    Southern_Warrior(std::string, int, int, std::string, int, bool, int, std::string, int, bool, int);
    void show() override;
};


#endif //MAP_H_SOUTHERN_WARRIOR_H
