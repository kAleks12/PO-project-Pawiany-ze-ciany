#ifndef MAP_H_WEAPON_H
#define MAP_H_WEAPON_H

#include <string>


class Weapon {
private:
    std::string name_;
    int damage_;
    bool bothHanded_;
    int slowdown_;
public:
    Weapon();
    void Show();
    void Fill(std::string, int, bool, int);
};


#endif //MAP_H_WEAPON_H
