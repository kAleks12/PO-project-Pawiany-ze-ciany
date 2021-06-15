#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Field.h"

std::mt19937 Field::fieldEngine{std::random_device{}()};

Field::Field() {    //creating field
    heroesAtThisField_[0] = nullptr;
    heroesAtThisField_[1] = nullptr;

    //Sleep(1000);

    int terrainNumber = randomNumber(0, 4);

    switch (terrainNumber) {    //randomly choosing terrain type
        case 0:
            terrainType_ = "forest";
            //std::cout << "forest" << std::endl;
            break;

        case 1:
            terrainType_ = "mountains";
            //std::cout << "mountains" << std::endl;
            break;

        case 2:
            terrainType_ = "desert";
            //std::cout << "desert" << std::endl;
            break;

        case 3:
            terrainType_ = "lake";
            //std::cout << "lake" << std::endl;
            break;

        case 4:
            terrainType_ = "plain";
            //std::cout << "plain" << std::endl;
            break;

    }

}

void Field::addBeing( Being * hero) {   //adding heroes to fields

    if((hero != nullptr) && isSpace()){
        if(heroesAtThisField_[0] == nullptr)
            heroesAtThisField_[0] = hero;
        else{
            heroesAtThisField_[1] = hero;
        }
    }
    else std::cout << "Field is full or hero corrupted";

}
void Field::addItem(int itemId) {   //putting items on field

    Item tmp(itemId);
    itemsAtThisField_.push_back(tmp);

}
/*
void Field::addItem(Item item) {   //other version of version above

    try {
        itemsAtThisField_.push_back(item);
    }
    catch( const std::bad_alloc & badAlloc) {
        std::cout << "Program crashed in Field::addItem :)";
        exit(69);
    }

}
*/
void Field::deleteItem() {      //removing item from field

    itemsAtThisField_.pop_back();

}
void Field::removeBeing(int position) {     //removing being from certain position on field

    heroesAtThisField_[position] = nullptr;

}

Being * Field::getHero(int pos) {   //WHO ARE YOU AND WHAT ARE YOU DOING ON MY SWAMP

    return heroesAtThisField_[pos];//*all star starts playing*

}
int Field::getItemsNum() {

    return itemsAtThisField_.size();

}
Item Field::copyItem() {

    return itemsAtThisField_.back();

}
void Field::showField() {   //printing fields content (heroes)

    if ((isPosEmpty(0)) && (isPosEmpty(1)))
        std::cout << "Field is empty" << std::endl;
    else {
        std::cout << "Field's content: \n\n";
        if (heroesAtThisField_[0] != nullptr) {
            std::cout << "Hero 1 \n";
            (heroesAtThisField_[0])->show();
        }
        if (heroesAtThisField_[1] != nullptr) {
            std::cout << "Hero 2: \n";
            (heroesAtThisField_[1])->show();
        }
    }

}

void Field::printItems() {  //printing fields content (items)

    for(auto & item: itemsAtThisField_){
        std::cout << item.getName() << " + ";
    }
    std::cout << std::endl;

}

bool Field::isPosEmpty(int pos) {   //checking whether specific one of two positions on field is empty

    return (heroesAtThisField_[pos] == nullptr);

}
bool Field::isSpace() {     //checking whether at least one of two positions on field is empty

    return !((heroesAtThisField_[0] != nullptr) && (heroesAtThisField_[1] != nullptr));
}

std::string Field::getTerType() {
    return terrainType_;
}

int Field::randomNumber(int min, int max) {  //PO final grades generator

    std::uniform_int_distribution<int> numRange(min, max);
    int randomNum;

    randomNum = numRange(fieldEngine);

    return randomNum;

}

