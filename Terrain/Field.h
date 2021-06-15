#ifndef PO_FIELD_H
#define PO_FIELD_H

#include <string>
#include "../Troops/Being.h"

class Field {
private:
    //PRIVATE ATTRIBUTES

    Being * heroesAtThisField_[2];
    std::vector <Item> itemsAtThisField_;
    std::string terrainType_;

public:
    //PUBLIC ATTRIBUTE
    static std::mt19937 fieldEngine;

    //CONSTRUCTOR
    Field();

    //SETTERS
    void addBeing(Being *);
    void removeBeing(int);
    void addItem(int);
    void deleteItem();

    //GETTERS
    std::string getTerType();
    Being * getHero(int);
    int getItemsNum();
    int randomNumber(int, int);
    Item copyItem();
    bool isPosEmpty(int);
    bool isSpace();

    //PRINTERS
    void showField();
    void printItems();
};


#endif //PO_FIELD_H
