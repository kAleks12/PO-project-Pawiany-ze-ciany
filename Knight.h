#ifndef MAP_H_KNIGHTS_H
#define MAP_H_KNIGHTS_H

#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class Knight:public Being{
    Weapon hisWeapon_;
    Armor hisArmor_;
public:
    Knight();
    void Show();
    Knight(std::string, int, int, std::string, int, bool, int, std::string, int, int);

};


#endif //MAP_H_KNIGHTS_H
