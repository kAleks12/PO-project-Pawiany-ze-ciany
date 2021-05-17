#include "Map.h"

void Map::spawn(Being * hero, int xPos, int yPos) {
    if(fields_[xPos][yPos].isSpace()) fields_[xPos][yPos].addBeing(hero);
}

void Map::changePos(Being* hero, int verChange, int horChange) {
    int currX = getX(hero);
    int currY = getY(hero);
    int pos = getPos(hero);
    int newX = boundaryCheck(currX + horChange);
    int newY = boundaryCheck(currY + verChange);

    if((!isFieldFull(newX, newY))&&(!isPosEmpty(currX, currY, pos))) {
        fields_[newY][newX].addBeing(fields_[currY][currX].getHero(pos));
        fields_[currY][currX].removeBeing(pos);
        std::cout << "Hero " << hero->getId() << " moved from " << currX << ", " << currY << " to " << newX << ", " << newY << std::endl;
    }
    else std::cout << "Where is full, or From is empty! Spadaj na drzewo" << std::endl;
}

void Map::addHero(Being* hero) {
    allHeroes_.push_back(hero);
}

void Map::removeHero(Being* hero){
    auto pos = std::find(allHeroes_.begin(), allHeroes_.end(), hero);
    allHeroes_.erase(pos);
}

int Map::boundaryCheck(int where) {
    if(where >= mapSize_)
        where = mapSize_-1;
    if(where < 0)
        where = 0;
    return where;
}

void Map::show() {
    int height = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    /*for (Being* n : allHeroes_) {
        std::cout << n-> getId() << std::endl;
    }*/
    std::cout << allHeroes_.size();
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
                if(j.getHero(0) != nullptr) std::cout << " " << j.getHero(0) -> getId() << "/";
                else std::cout << " ----/";
                if(j.getHero(1) != nullptr) std::cout << j.getHero(1) -> getId();
                else std::cout << "----";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
        std::cout << " " << height++ << " ||\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    std::cout << "===========================================================================================================\n";
}
////////////////////////////////////////////

bool Map::isFieldFull(int xPos, int yPos) {
    return !(fields_[yPos] [xPos].isSpace());
}

 bool Map::isPosEmpty(int xPos, int yPos, int pos) {
    return (fields_[yPos] [xPos].isPosEmpty(pos));
}

//////////////////////////////////////////////
void Map::getItems(Field field, Being * hero) {
    while(field.areItems()) hero -> addItem(field.giveItem());
}

int Map::getMapSize() {
    return mapSize_*mapSize_;
}

int Map::getX(Being* hero) {
    for(int i=0; i<mapSize_;i++){
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return j;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return j;
        }
    }
    return -10;
}

int Map::getY(Being* hero) {
    for(int i=0; i<mapSize_;i++){
        for(int j=0; j<mapSize_; j++){
            if(fields_[i][j].getHero(0)!=nullptr)
                if(fields_[i][j].getHero(0)->getId() == hero -> getId()) return i;
            if(fields_[i][j].getHero(1)!=nullptr)
                if(fields_[i][j].getHero(1)->getId() == hero -> getId() ) return i;
        }
    }
    return -10;
}

int Map::getPos(Being* hero) {
    for(auto & field : fields_){
        for(auto & j : field){
            if(j.getHero(0)!=nullptr)
                if(j.getHero(0)->getId() == hero -> getId()) return 0;
            if(j.getHero(1)!=nullptr)
                if(j.getHero(1)->getId() == hero -> getId() ) return 1;
        }
    }
    return -10;
}
/////////////////////////////////////////////

void Map::showField(int xPos, int yPos) {
    fields_[xPos][yPos].showField();
}

void Map::move(Being* hero, int moveDirection) {

    int verChange = 0;
    int horChange = 0 ;
    switch (moveDirection) {
        case 0:
            verChange = -(hero->getSpeed());
            break;
        case 1:
            verChange = -(hero->getSpeed());
            horChange = -(hero->getSpeed());
            break;
        case 2:
            horChange = -(hero->getSpeed());
            break;
        case 3:
            verChange = hero->getSpeed();
            horChange = -(hero->getSpeed());
            break;
        case 4:
            verChange = hero->getSpeed();
            break;
        case 5:
            verChange = hero->getSpeed();
            horChange = hero->getSpeed();
            break;
        case 6:
            horChange = hero->getSpeed();
            break;
        case 7:
            verChange = -(hero->getSpeed());
            horChange = hero->getSpeed();
            break;
        default:
            std::cout << "Wrong direction!";
    }
    changePos(hero, verChange, horChange);

}

void Map::encounter(Field & field, int startingPos){
    if(startingPos == 0){
        field.getHero(1)->changeHp(-(field.getHero(0)->getTotalAttackPower()));
        if(field.getHero(1)->isAlive())
            field.getHero(0)->changeHp(-(field.getHero(1)->getTotalAttackPower()/2));
    }
    else {
        field.getHero(0)->changeHp(-(field.getHero(1)->getTotalAttackPower()));
        if(field.getHero(0)->isAlive())
            field.getHero(1)->changeHp(-(field.getHero(0)->getTotalAttackPower()/2));
    }

    if(!(field.getHero(0)->isAlive()))
        field.removeBeing(0);
    if(!(field.getHero(1)->isAlive()))
        field.removeBeing(1);
}

void Map::iteration()
{
    srand(time(nullptr));
        for(auto & hero : allHeroes_) {
            if(getX(hero)!=-10) {
                int movement = rand() % 8;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                move(hero, movement);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                getItems(fields_[getX(hero)][getY(hero)], hero);
                if (isFieldFull(getX(hero), getY(hero))) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    std::cout << "ENCOUNTER!!!!" << std::endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
                    encounter(fields_[getY(hero)][getX(hero)], getPos(hero));
                }
            }
            else{
            }
        }
}