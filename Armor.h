#ifndef MAP_H_ARMOR_H
#define MAP_H_ARMOR_H

#include <string>

class Armor {
private:
    std::string name_;
    int armorPoints_;
    int weight_;
public:
    Armor();
    void show();
    void fill(std::string, int, int);

};


#endif //MAP_H_ARMOR_H
