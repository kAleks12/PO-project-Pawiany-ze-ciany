#ifndef PO_BEING_H
#define PO_BEING_H

#include <string>
#include <random>

class Being {
protected:
    int healthPoints_ = 100;
    std::string name_;
    int strength_;
    int speed_;
    int posX_;
    int posY_;
    char id_ [4];
public:
    Being();
    Being(std::string, int, int );
    virtual void show();
    void changeHp(int);
    std::string  getId();
};


#endif //PO_BEING_H
