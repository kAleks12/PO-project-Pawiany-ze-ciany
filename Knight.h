#ifndef MAP_H_KNIGHTS_H
#define MAP_H_KNIGHTS_H

#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class Knight:public Being{
    Weapon objWeapon_;
    Armor objArmor_;
public:
    Knight();
    Knight(std::string, int, int, std::string, int, bool, int, std::string, int, int);

    void show() override;
};


#endif //MAP_H_KNIGHTS_H
