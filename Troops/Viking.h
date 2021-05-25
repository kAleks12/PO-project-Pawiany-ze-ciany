//
// Created by Michał on 15.04.2021.
//

#ifndef PO_VIKING_H
#define PO_VIKING_H

#include "Being.h"

class Viking: public Being {
private:
    static int numOfVikingsCreated_;
    std::string objArmor_;
    std::string objWeapon_;

public:
    Viking();
    explicit Viking(std::string, int);
    ~Viking();

    void show() override;
    void destroy() override;
};


#endif //PO_VIKING_H
