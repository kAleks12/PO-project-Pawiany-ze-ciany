
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

void Map::show() {
    std::cout << "=====================================================================================================\n";
    for(int i = 0; i < mapSize_;i++){
        for(int j = 0; j < mapSize_; j++){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            if(fields_[i][j].isEmpty()) std::cout << " + empty +";
            else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                if(fields_[i][j].heroesAtThisField_[0] != nullptr) std::cout << " " << fields_[i][j].heroesAtThisField_[0] -> getId() << "/";
                else std::cout << " ----/";
                if(fields_[i][j].heroesAtThisField_[1] != nullptr) std::cout << fields_[i][j].heroesAtThisField_[1] -> getId();
                else std::cout << "----";
            }
        }
        std::cout << "\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    std::cout << "=====================================================================================================\n";
}

int Map::drawPos() {
    srand(time(nullptr));
    std::random_device rd;
    std::mt19937 randomSeed(rd());
    std::uniform_int_distribution<int> posRange(0, (mapSize_)-1);
    int randomNum;

    for(int i = 0; i < rand() % 10000;i++) randomNum = posRange(randomSeed);
    return randomNum;
}
