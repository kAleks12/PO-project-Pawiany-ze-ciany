#ifndef PO_FIELD_H
#define PO_FIELD_H


#include "Being.h"

class Field {

    Being whatContains_[2];
    bool isEmpty_;
    int xCoord_;
    int yCoord_;
public:
    void addBeing(int,Being);
    void removeBeing(int);
    void removeBeing();
};


#endif //PO_FIELD_H
