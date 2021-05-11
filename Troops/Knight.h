#ifndef MAP_H_KNIGHTS_H
#define MAP_H_KNIGHTS_H

#include "Being.h"

class Knight: public Being{
    static int numOfKnightsCreated_;
    static int moveCap_;
    std::string objArmor_;
    std::string objWeapon_;
    bool isOnHorse;
public:
    Knight();
    explicit Knight(std::string, int);

    void changeStatus();
    void show() override;
};

#endif //MAP_H_KNIGHTS_H