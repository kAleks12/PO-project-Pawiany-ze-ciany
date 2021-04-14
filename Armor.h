#ifndef MAP_H_ARMOR_H
#define MAP_H_ARMOR_H

#include <string>

class Armor {
private:
    std::string name_;
    int armorPoints_;
    int slowdown_;
public:
    Armor();
    void Show();
    void Fill(std::string, int, int);

};


#endif //MAP_H_ARMOR_H
