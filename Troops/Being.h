#ifndef PO_BEING_H
#define PO_BEING_H

#include "../Items/Item.h"

#include <string>
#include <cstdio>
#include <random>


class Being {
protected:
    std::string name_;
    int healthPoints_ = 100;
    int strength_;
    int speed_;
    int tribe_;
    char id_ [81];
    std::vector <Item> backpack_;
public:
    Being();
    ~Being();

    void changeHp(int);
    void addItem(const Item&);

    bool isAlive();

    std::string getId();
    int getTotalAttackPower();
    int getSpeed() const;
    [[nodiscard]] int getTribe() const;

    virtual void show() = 0;
    virtual void destroy() = 0;
};

#endif //PO_BEING_H
