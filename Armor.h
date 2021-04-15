#ifndef MAP_H_ARMOR_H
#define MAP_H_ARMOR_H

#include <string>

class Armor {
private:
    int armorPoints_;
    int weight_;
    int wearPoints_ = 100;
public:
    Armor();
    void show();
    void fill(int, int);

};


#endif //MAP_H_ARMOR_H
