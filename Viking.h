//
// Created by Michał on 15.04.2021.
//

#ifndef PO_VIKING_H
#define PO_VIKING_H

#include "Being.h"
#include "Weapon.h"
#include "Armor.h"

class Viking: public Being {
private:
    static int numOfVikingsCreated_;
    static int numOfVikingsAlive_;
    Weapon objWeapon_;
    Armor objArmor_;
public:
    Viking();
    Viking(std::string);

    void show() override;
};


#endif //PO_VIKING_H
