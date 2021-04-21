#ifndef MAP_H_SLAV_H
#define MAP_H_SLAV_H

#include "Being.h"

class Slav: public Being{
private:
    static int numOfSlavsCreated_;
    std::string objArmor_;
    std::string objWeapon_;
public:
    Slav();
    explicit Slav(std::string);

    void show() override;

};


#endif //MAP_H_SLAV_H
