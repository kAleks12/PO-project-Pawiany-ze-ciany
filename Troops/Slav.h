#ifndef MAP_H_SLAV_H
#define MAP_H_SLAV_H

#include "Being.h"

class Slav: public Being{
private:
    static int numOfSlavsCreated_;
    static int moveCap_;
    std::string objArmor_;
    std::string objWeapon_;
public:
    Slav();
    explicit Slav(std::string, int);

    void show() override;

};


#endif //MAP_H_SLAV_H
