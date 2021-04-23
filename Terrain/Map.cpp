#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {
    if(fields_[xPos][yPos].isSpace()) fields_[xPos][yPos].addBeing(hero);
}

void Map::remove(int xPos, int yPos, int position) {
    fields_[xPos][yPos].removeBeing(position);
}

bool Map::isFieldFull(int xPos, int yPos) {
    return !(fields_[xPos] [yPos].isSpace());
}

bool Map::isPosEmpty(int xPos, int yPos, int pos) {
    return (fields_[xPos] [yPos].isPosEmpty(pos));
}

int Map::getMapSize() {
    return mapSize_*mapSize_;
}

Being * Map::fieldGetHero(int xPos, int yPos, int pos) {
    return fields_[xPos][yPos].getHero(pos);
}

void Map::show() {
    int height = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    std::cout << "                                            Game Map\n";
    std::cout << "===========================================================================================================\n";
    std::cout << "||     0         1         2         3         4         5         6         7         8         9       ||\n";
    for(auto & field : fields_){
        std::cout << "||";
        for(auto & j : field){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            if(j.isPosEmpty(0)&&j.isPosEmpty(1)) std::cout << " + empty +";
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                if(j.heroesAtThisField_[0] != nullptr) std::cout << " " << j.heroesAtThisField_[0] -> getId() << "/";
                else std::cout << " ----/";
                if(j.heroesAtThisField_[1] != nullptr) std::cout << j.heroesAtThisField_[1] -> getId();
                else std::cout << "----";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        std::cout << " " << height++ << " ||\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    std::cout << "===========================================================================================================\n";
}

void Map::showField(int xPos, int yPos) {
    fields_[xPos][yPos].showField();
}

void Map::move(int fromX, int fromY, int pos, int whereX, int whereY) {
    if((!isFieldFull(whereX, whereY))&&(!isPosEmpty(fromX, fromY, pos))) {
        fields_[whereX][whereY].addBeing(fields_[fromX][fromY].getHero(pos));
        fields_[fromX][fromY].removeBeing(pos);
    }
    else std::cout << "Where is full, or From is empty" << std::endl;
}
