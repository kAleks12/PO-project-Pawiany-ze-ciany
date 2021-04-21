
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

bool Map::isFieldEmpty(int xPos, int yPos, int pos) {
    return (fields_[xPos] [yPos].isEmpty(pos));
}

int Map::getMapSize() {
    return mapSize_*mapSize_;
}

Being * Map::fieldGetHero(int xPos, int yPos, int pos) {
    return fields_[xPos][yPos].getHero(pos);
}

int Map::drawPos() {
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 randomSeed(rd());
    std::uniform_int_distribution<int> posRange(0, (mapSize_)-1);
    int randomNum;

    while(rand () % 5 != 2) randomNum = posRange(randomSeed);
    return randomNum;
}

void Map::show() {
    int height = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    std::cout << "                                           Game Map\n";
    std::cout << "===========================================================================================================\n";
    std::cout << "||     0         1         2         3         4         5         6         7         8         9       ||\n";
    for(auto & field : fields_){
        std::cout << "||";
        for(auto & j : field){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            if(j.isEmpty(0)&&j.isEmpty(1)) std::cout << " + empty +";
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