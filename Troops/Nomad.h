#ifndef MAP_H_SOUTHERN_WARRIOR_H
#define MAP_H_SOUTHERN_WARRIOR_H

#include "Being.h"

class Nomad: public Being{
private:
    static int numOfNomadsCreated_;
    std::string objArmor_;
    std::string objWeapon_;
public:
    Nomad();
    explicit Nomad(std::string);

    void show() override;
};


#endif //MAP_H_SOUTHERN_WARRIOR_H
