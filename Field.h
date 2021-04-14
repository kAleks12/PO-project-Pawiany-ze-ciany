#ifndef PO_FIELD_H
#define PO_FIELD_H


#include "Being.h"

class Field {

    Being* whatContains_[2];
    bool isEmpty_;
public:
    Field();
    void addBeing(Being *);
    void removeBeing(int);
    void showField();
    bool isEmpty();
};


#endif //PO_FIELD_H
