#ifndef PO_FIELD_H
#define PO_FIELD_H

#include <string>
#include "../Troops/Being.h"

class Field {
private:
    Being * heroesAtThisField_[2];
    std::vector <Item> itemsAtThisField_;
public:
    Field();
    void addBeing(Being *);
    void removeBeing(int);
    Being * getHero(int);
    bool isPosEmpty(int);
    bool isSpace();
    void showField();
    void addItem(int);
    Item giveItem();

    bool areItems();
};


#endif //PO_FIELD_H
