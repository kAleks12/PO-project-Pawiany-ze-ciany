#ifndef PO_BEING_H
#define PO_BEING_H

#include "../Items/Item.h"

#include <string>
#include <random>


class Being {
protected:
    int healthPoints_ = 100;
    std::string name_;
    int strength_;
    int speed_;
    int posX_;
    int posY_;
    char id_[4];
    std::vector <Item> backpack_;
public:
    Being();
    void changeHp(int);
    void setCoords(int, int);
    std::string getId();
    float getTotalAttackPower();
    virtual void show();
    void move(int posX, int posY);
};

#endif //PO_BEING_H
