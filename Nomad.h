#ifndef MAP_H_SOUTHERN_WARRIOR_H
#define MAP_H_SOUTHERN_WARRIOR_H

#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class Nomad: public Being{
private:
    static int numOfWarriorsCreated_;
    static int numOfWarriorAlive_;
    Weapon objWeapon_;
    Weapon objWeapon2_;
public:
    Nomad();
    Nomad(std::string);
    void show() override;
};


#endif //MAP_H_SOUTHERN_WARRIOR_H
