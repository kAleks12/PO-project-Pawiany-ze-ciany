#ifndef PO_FIELD_H
#define PO_FIELD_H

#include <string>
#include "Being.h"

class Field {

    friend class Map;
    Being* heroesAtThisField_[2];
    bool isEmpty_;
public:
    Field();
    void addBeing(Being *);
    void removeBeing(int);
    void show();
    bool isEmpty();

    std::string getNames();
};


#endif //PO_FIELD_H
