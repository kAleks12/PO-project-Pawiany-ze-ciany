#ifndef PO_FIELD_H
#define PO_FIELD_H

#include <string>
#include "../Troops/Being.h"

class Field {
    friend class Map;
private:
    Being * heroesAtThisField_[2];
public:
    Field();
    void addBeing(Being *);
    void removeBeing(int);
    Being * getHero(int);
    bool isPosEmpty(int);
    bool isSpace();
    void showField();
};


#endif //PO_FIELD_H
