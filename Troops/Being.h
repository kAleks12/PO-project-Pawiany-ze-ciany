#ifndef PO_BEING_H
#define PO_BEING_H

#include "../Items/Item.h"

#include <string>
#include <cstdio>
#include <random>


class Being {
protected:
    int healthPoints_ = 100;
    std::string name_;
    int strength_;
    int tribe_;
    char id_ [81];
    std::vector <Item> backpack_;
public:
    Being();
    void changeHp(int);
    std::string getId();
    float getTotalAttackPower();
    [[nodiscard]] int getTribe() const;
    virtual void show();
    void addItem(const Item&);
    bool isAlive();
};

#endif //PO_BEING_H
