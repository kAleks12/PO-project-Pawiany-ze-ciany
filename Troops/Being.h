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
    void setHP(int hpMod); //CHANGING HP BY hpMod
    void addKill();
    void addItem(const Item&);
    void useTmpItems(); //USING ONE OF TEMPORARY ITEMS IF POSSIBLE
    void updateWeapon(); //UPDATING WEAPON AFTER PICKING UP A BETTER ONE
    void deactivateItem(const std::string&); //CHANGING ITEM'S STATE TO 'UNUSED';
    void setDeathIteration(int);

    //GETTERS
    std::string getId();
    std::string getName();
    int getHP();
    int getSpeed() const;
    int getTribeId() const;
    std::string getTribe() const; //GET TRIBE'S NAME
    int getKills();
    int getDeathIt();

    int getTotalAP(); //GETTING TOTAL ATTACK POWER (WEAPON, ACTIVE POTIONS)
    int getDefense(); //GETTING TOTAL DEFENSE POWER (ARMOR, ACTIVE POTIONS)

    Item findItem(const std::string& name); //FINDING ITEM WITH A SPECIFIED NAME IN HERO'S BACKPACK
    std::string findArmor(); //FINDING ACTIVELY USED ARMOR IN HERO'S BACKPACK
    std::string findWeapon(); //FINDING ACTIVELY USED WEAPON IN HERO'S BACKPACK
    std::string findPotion(std::string); //FINDING POTION WITH A SPECIFIED NAME IN HERO'S BACKPACK
    bool isAlive();
    bool whetherPickUp(const Item &); //CHECKING WHETHER HERO SHOULD TAKE ITEM


    //PRINTERS
    void printBackpack(); //PRINTING ALL ITEMS
    virtual void show() = 0;
    virtual void destroy() = 0;


};

#endif //PO_BEING_H
