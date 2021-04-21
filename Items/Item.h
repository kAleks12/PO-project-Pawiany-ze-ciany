//
// Created by Kacper Aleks on 21.04.2021.
//

#ifndef PO_ITEM_H
#define PO_ITEM_H

#include <string>
#include <map>
#include <iostream>


class Item {
    friend class Being;
private:
    bool isTimeLim_;
    int duration_;
    bool isBeingUsed_ = false;
    std::string name_;
    int healthBoost_;
    float attackBoost_;
    int speedBoost_;
    int armorBoost_;
    int weight_;
public:
    explicit Item(int);
    explicit Item(const std::string &);
    std::string getName();
    void show();
};


#endif //PO_ITEM_H
