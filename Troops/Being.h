#ifndef PO_BEING_H
#define PO_BEING_H

#include "../Items/Item.h"

#include <string>
#include <cstdio>
#include <random>
#include <fstream>


class Being {
protected:
    //ATTRIBUTES
    std::string name_;
    char id_ [81];
    char tribe_[10];
    int healthPoints_ = 100;
    int strength_;
    int speed_;
    int tribeId_;
    int killCounter_ = 0;
    int deathIteration_= -1;

    std::vector <Item> backpack_;

public:
    //CONSTRUCTOR AND DESTRUCTOR
    Being();
    ~Being();

    //SETTERS
    void changeHp(int);
    void addKill();
    void addItem(const Item&);
    void useTmpItems();
    void updateWeapon();
    void deactivateItem(const std::string&);
    void setDeathIteration(int);

    //GETTERS
    std::string getId();
    std::string getName();
    int getHP();
    int getSpeed() const;
    int getTribeId() const;
    std::string getTribe() const;
    int getKills();
    int getDeathIt();

    int getTotalAP();
    int getDefense();

    Item findItem(const std::string&);
    std::string findArmor();
    std::string findWeapon();
    std::string findPotion(std::string);

    bool isAlive();
    bool whetherPickUp(const Item &);


    //PRINTERS
    void printBackpack();
    virtual void show() = 0;
    virtual void destroy() = 0;


};

#endif //PO_BEING_H
