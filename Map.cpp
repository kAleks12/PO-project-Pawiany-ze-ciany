
#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {
    if(fields_[xPos][yPos].isEmpty()) fields_[xPos][yPos].addBeing(hero);
}

void Map::remove(int xPos, int yPos, int position) {
    fields_[xPos][yPos].removeBeing(position);

}

bool Map::isFieldEmpty(int xPos, int yPos) {
    return fields_[xPos] [yPos].isEmpty();
}

void Map::show() {
    std::cout << "=================================================\n||";
    for(int i=0;i<mapSize_;i++){
        for(int j=0;j<mapSize_;j++){
            if(fields_[i][j].isEmpty()) std::cout << " - ";
            else std::cout << " " << fields_[i][j].heroesAtThisField_[j%2] -> getId() << " ";
        }
        std::cout << "\n";
    }
    std::cout << "=================================================\n";
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
