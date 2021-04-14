#ifndef MAP_H_SLAV_H
#define MAP_H_SLAV_H

#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class Slav: public Being{
private:
    Weapon objWeapon_;
public:
    Slav();
    Slav(std::string, int, int, std::string, int, bool, int);

    void show() override;

};


#endif //MAP_H_SLAV_H
