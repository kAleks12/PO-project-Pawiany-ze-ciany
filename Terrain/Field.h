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
    Field(); //creating field

    //SETTERS
    void addBeing(Being *); //adding heroes to fields
    void removeBeing(int); //removing being from certain position on field
    void addItem(int); //putting items on field
    void deleteItem(); //removing item from field

    //GETTERS
    std::string getTerType();
    Being * getHero(int);
    int getItemsNum();
    int randomNumber(int, int);
    Item copyItem();
    bool isPosEmpty(int); //checking whether specific one of two positions on field is empty
    bool isSpace(); //checking whether at least one of two positions on field is empty

    //PRINTERS
    void showField(); //printing fields content (heroes)
    void printItems(); //printing fields content (items)
};


#endif //PO_FIELD_H
