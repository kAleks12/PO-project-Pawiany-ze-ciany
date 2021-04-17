#ifndef PO_FIELD_H
#define PO_FIELD_H

#include <string>
#include "Being.h"

class Field {

    friend class Map;
    Being * heroesAtThisField_[2];
public:
    Field();
    void addBeing(Being *);
    void removeBeing(int);
    void show();
    bool isEmpty(int);
    bool isSpace();
    void showField();
    Being * getHero(int);
};


#endif //PO_FIELD_H
