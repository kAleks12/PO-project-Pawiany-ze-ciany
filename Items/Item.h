//
// Created by Kacper Aleks on 21.04.2021.
//

#ifndef PO_ITEM_H
#define PO_ITEM_H

#include <string>
#include <iostream>
#include <map>
#include <windows.h>


class Item {
    friend class Being;
private:
    std::string name_;
    int armorPoints_;
    int attackPoints_;
    int healthBoost_;
    int speedBoost_;

    bool isBeingUsed_ = false;
    bool isTmp_;

    int duration_=0;
public:
    explicit Item(int);
    explicit Item(const std::string &);

    void changeState();

    std::string getName();

    void show();
    void destroy();
};


#endif //PO_ITEM_H+30