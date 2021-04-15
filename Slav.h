#ifndef MAP_H_SLAV_H
#define MAP_H_SLAV_H

#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class Slav: public Being{
private:
    static int numOfSlavsCreated_;
    static int numOfSlavsAlive_;
    Weapon objWeapon_;
public:
    Slav();
    Slav(std::string);

    void show() override;

};


#endif //MAP_H_SLAV_H
