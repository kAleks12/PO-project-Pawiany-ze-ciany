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
    void changeWeapon();
    void useTempItems();
    void deactivateItem(const std::string&);

    std::string getId();
    int getHP();
    int getTotalAP();
    int getDefense();
    [[nodiscard]] int getSpeed() const;
    [[nodiscard]] int getTribe() const;

    Item findItem(const std::string&);

    std::string findArmor();
    std::string findWeapon();
    std::string findPotion(std::string);

    void printBackpack();
    virtual void show() = 0;
    virtual void destroy() = 0;

    bool isAlive();
    bool whetherPickUp(const Item &);
};

#endif //PO_BEING_H
