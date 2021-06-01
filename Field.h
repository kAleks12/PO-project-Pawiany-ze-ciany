#ifndef PO_FIELD_H
#define PO_FIELD_H

#include <string>
#include "../Troops/Being.h"

class Field {
private:
    Being * heroesAtThisField_[2];
    std::vector <Item> itemsAtThisField_;
    std::string terrainType_;
public:
    static std::mt19937 fieldEngine;
    Field();

    void addBeing(Being *);
    void addItem(int);
    void addItem(Item);
    void deleteItem();
    void removeBeing(int);
    std::string getTerrain();

    Being * getHero(int);
    int getItemsNum();
    int randomNumber(std::mt19937 &, int, int);
    Item copyItem();

    void showField();
    void printItems();

    bool isPosEmpty(int);
    bool isSpace();
};


#endif //PO_FIELD_H
