#ifndef MAP_H_KNIGHTS_H
#define MAP_H_KNIGHTS_H

#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

#include <iostream>

class Knight:public Being{
    static int numOfKnightsCreated_;
    static int numOfKnightsAlive_;
    Weapon objWeapon_;
    Armor objArmor_;
public:
    Knight();
    Knight(std::string);

    void show() override;
};


#endif //MAP_H_KNIGHTS_H