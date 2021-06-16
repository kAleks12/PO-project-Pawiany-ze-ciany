//
// Created by Kacper Aleks on 21.04.2021.
//

#ifndef PO_ITEM_H
#define PO_ITEM_H

#include <string>
#include <iostream>
#include <map>
#include <windows.h>

#include "../Config.h"
#include "../COUT.h"

class Item {
    friend class Being;
private:
    //STATIC ATTRIBUTES
    std::string name_;
    int armorPoints_;
    int attackPoints_;
    int healthBoost_;
    int speedBoost_;

    //ATTRIBUTES CONNECTED WITH TEMPORALITY
    bool isBeingUsed_ = false;
    bool isTmp_;
    int duration_=0;

public:
    //CONSTRUCTORS
    explicit Item(int); //generating item type
    explicit Item(const std::string &); //generating item details

    //SETTERS
    void changeState(); //changing item state (used/unused)

    //GETTERS
    std::string getName();

    //PRINTERS
    void show(); //printing item details
};


#endif //PO_ITEM_H+30