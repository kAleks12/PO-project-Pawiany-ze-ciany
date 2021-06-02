#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Field.h"

std::mt19937 Field::fieldEngine{std::random_device{}()};

Field::Field() {
    heroesAtThisField_[0] = nullptr;
    heroesAtThisField_[1] = nullptr;

    //Sleep(1000);

    int terrainNumber = randomNumber(fieldEngine, 0, 4);

    switch (terrainNumber) {
        case 0:
            terrainType_ = "forest";
            std::cout<<"LAS\n";
            break;

        case 1:
            terrainType_ = "mountains";
            std::cout<<"GORY\n";
            break;

        case 2:
            terrainType_ = "desert";
            std::cout<<"PUSTYNIA\n";
            break;

        case 3:
            terrainType_ = "lake";
            std::cout<<"JEZIORO\n";
            break;

        case 4:
            terrainType_ = "plain";
            std::cout<<"NIZINY\n";
            break;

    }

}

void Field::addBeing( Being * hero) {

    if((hero != nullptr) && isSpace()){
        if(heroesAtThisField_[0] == nullptr)
            heroesAtThisField_[0] = hero;
        else{
            heroesAtThisField_[1] = hero;
        }
    }

}
void Field::addItem(int itemId) {

    Item tmp(itemId);
    try {
        itemsAtThisField_.push_back(tmp);
    }
    catch(std::bad_alloc & badAlloc) {
        std::cout << "Program crashed in Field::addItem :)";
        exit(69);
    }

}
void Field::addItem(Item item) {

    try {
        itemsAtThisField_.push_back(item);
    }
    catch( const std::bad_alloc & badAlloc) {
        std::cout << "Program crashed in Field::addItem :)";
        exit(69);
    }

}
void Field::deleteItem() {

    itemsAtThisField_.pop_back();

}
void Field::removeBeing(int position) {

    heroesAtThisField_[position] = nullptr;

}

Being * Field::getHero(int pos) {

    return heroesAtThisField_[pos];

}
int Field::getItemsNum() {

    return itemsAtThisField_.size();

}
Item Field::copyItem() {

    return itemsAtThisField_.back();

}

void Field::showField() {

    if((isPosEmpty(0))&&(isPosEmpty(1)))
        std::cout << "Pole jest puste" << std::endl;
    else {
        std::cout << "Zawartosc pola: \n\n";
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
void Field::printItems() {

    for(auto & item: itemsAtThisField_){
        std::cout << item.getName() << " + ";
    }
    std::cout << std::endl;

}

bool Field::isPosEmpty(int pos) {

    return (heroesAtThisField_[pos] == nullptr);

}
bool Field::isSpace() {

    return !((heroesAtThisField_[0] != nullptr) && (heroesAtThisField_[1] != nullptr));
}

std::string Field::getTerrain() {
    return terrainType_;
}

int Field::randomNumber(std::mt19937 & engine, int min, int max) {
    std::uniform_int_distribution<int> posRange(min, max);
    int randomNum;
    randomNum = posRange(engine);
    return randomNum;

}

