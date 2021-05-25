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
    void addItem(int);
    void addItem(Item);
    void removeBeing(int);
    Item giveItem();

    Being * getHero(int);
    int getItemsNum();

    void showField();
    void printItems();

    bool isPosEmpty(int);
    bool isSpace();
};


#endif //PO_FIELD_H
