//
// Created by Kacper Aleks on 12.04.2021.
//

#ifndef PO_BEING_H
#define PO_BEING_H

#include <string>

class Being {
private:
    int healthPoints_ ;
    std::string name_;
    int attackDamage_;
    int speed_;
public:
    Being(std::string, int, int);
    void Show();
};


#endif //PO_BEING_H
