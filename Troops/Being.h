#ifndef PO_BEING_H
#define PO_BEING_H

#include "../Items/Item.h"

#include <string>
#include <cstdio>
#include <random>
#include <fstream>


class Being {
protected:
    std::string name_;
    char id_ [81];

    int healthPoints_ = 100;
    int strength_;
    int speed_;
    int tribe_;
    int killCounter_ = 0;

    std::vector <Item> backpack_;
public:
    Being();
    ~Being();

    void changeHp(int);
    void addKill();
    void addItem(const Item&);
    void useTmpItems();
    void updateWeapon();
    void deactivateItem(const std::string&);

    std::string getId();
    std::string getName();
    int getHP();
    int getTotalAP();
    int getDefense();
    int getSpeed() const;
    int getTribe() const;
    int getKills();

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
