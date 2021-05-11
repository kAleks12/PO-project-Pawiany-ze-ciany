//
// Created by Michał on 15.04.2021.
//

#ifndef PO_VIKING_H
#define PO_VIKING_H

#include "Being.h"

class Viking: public Being {
private:
    static int numOfVikingsCreated_;
    static int moveCap_;
    std::string objArmor_;
    std::string objWeapon1_;
    std::string objWeapon2_;
public:
    Viking();
    explicit Viking(std::string, int);

    void show() override;
};


#endif //PO_VIKING_H
